#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h" 

typedef struct
{
    char            chunkID[5];	    // Информация о формате файла (должн быть RIFF)
    unsigned        chunkSize;	    // Размер без chunkId;
    char            format[5];	    // Формат потоковых данных (должн быть WAVE);
    
    char            subchunk1ID[5];	// Описание параметров WAV-файла ("fmt ");
    unsigned        subchunk1Size;	// Размер подструктуры  subchunk1;
    unsigned short	audioFormat;	// Аудио формат (PCM = 1);
    unsigned short	nChannels;      // Количество каналов (Моно = 1, Стерео = 2);
    unsigned	    samplesRate;    // Частота дискретизации в Гц;
    unsigned        byteRate;       // Кол-во передаваемых байт в секунду воспроизведения;
    unsigned short  blockAlign;     // Размер сэмпла в байтах 16 бит = 2 байта моно, 32 бита = 4 байта стерео (включая все каналы);
    unsigned short  bitsPerSample;  // Количество бит в сэмпле.
    
    char            subchunk2ID[5]; // Символы "data", начало чанка данных;
    unsigned        subchunk2Size;  // Размер области данных в байтах;
    short           *data;	        // Данные
    
} WavData;

/// @brief Читает данные с wav файла
/// @param data структура, куда записать данные
/// @param fileName название файла, который надо прочитать
/// @return выведет 1, если произойдёт ошибка, в ином случаи 0
int readWav(WavData *data, char *fileName)
{
    FILE *file;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
	    printf("Неможливо відкрити файл\n");
	    return 1;
    }

    //==== Читаем данние до первого подчанка ==========================================================
    // ID форматов и подчанков
    char nameRiff[5] = "RIFF\0";
    char nameWave[5] = "WAVE\0";
    char nameFmt[5] = "fmt \0";
    char nameData[5] = "data\0";

    fread(&data->chunkID, 4, 1, file);
    data->chunkID[4] = '\0';
    
    // Проверяем являеться ли этот файл аудиофайлом (равен ли chunkID "RIFF")
    if (strncmp(&nameRiff, data->chunkID, 5))
    {
        printf("Не правильный формат файла:\n   Это не аудиофайл!");
        return 1;
    }

    fread(&data->chunkSize, 4, 1, file);
    fread(&data->format, 4, 1, file);
    data->format[4] = '\0';
    
    // Проверяем являеться ли этот файл wav (равен ли format "WAVE")
    if (strncmp(&nameWave, data->format, 5))
    {
        printf("Не правильный формат файла:\n   Это не wave файл!");
        return 1;
    }

    //==== Читаем данние подчанка fmt ===============================================================================

    fread(&data->subchunk1ID, 4, 1, file);
    data->subchunk1ID[4] = '\0';
    
    // Проверяем являеться ли следующий подчанк "fmt ", в противнос случаи пропускаем подчанки пока его не найдём
    while (strncmp(&nameFmt, data->subchunk1ID, 5))
    {
        printf("Подзаголовок %s не data. Проверяем следующий подчанк\n", data->subchunk1ID);

        // Читаем размер неподходящего блока и пропускаем его
        unsigned sizeSubchunk;  
        fread(sizeSubchunk, 4, 1, file);
        char buffer[sizeSubchunk];
        fread(buffer, 1, sizeSubchunk, file);

        // Читаем ID следующего блока и проверяем его
        fread(&data->subchunk1ID, 4, 1, file);
    }

    fread(&data->subchunk1Size, 4, 1, file);
    fread(&data->audioFormat, 2, 1, file);
    fread(&data->nChannels, 2, 1, file);
    fread(&data->samplesRate, 4, 1, file);
    fread(&data->byteRate, 4, 1, file);
    fread(&data->blockAlign, 2, 1, file);
    fread(&data->bitsPerSample, 2, 1, file);


    //==== Читаем данние подчанка data ===============================================================================

    fread(&data->subchunk2ID, 4, 1, file);
    data->subchunk2ID[4] = '\0';
    
    // Проверяем являеться ли следующий подчанк "data", в противнос случаи пропускаем подчанки пока его не найдём
    while (strncmp(&nameData, data->subchunk2ID, 5))
    {
        printf("Подзаголовок %s не data. Проверяем следующий подчанк\n", data->subchunk2ID);

        // Читаем размер неподходящего блока и пропускаем его
        unsigned sizeSubchunk;  
        fread(sizeSubchunk, 4, 1, file);
        char buffer[sizeSubchunk];
        fread(buffer, 1, sizeSubchunk, file);

        // Читаем ID следующего блока и проверяем его
        fread(&data->subchunk2ID, 4, 1, file);
    }

    fread(&data->subchunk2Size, 4, 1, file);
    data->data =  (unsigned short*) malloc(data->subchunk2Size);
    fread(data->data, 2, data->subchunk2Size/2, file);

    fclose(file);
    return 0;
}

/// @brief Записываем изменённые данные в новый файл
/// @param data структура, откуда брать данные для записи
/// @param fileName название файла, в который записать данные
/// @param change_dB на сколько дБ изменить громкость
void writeWav(WavData *data, char *fileName, int change_dB)
{
    FILE *file;
    file = fopen(fileName, "wb");

    fwrite(&data->chunkID, 4, 1, file);
    fwrite(&data->chunkSize, 4, 1, file);
    fwrite(&data->format, 4, 1, file);
    fwrite(&data->subchunk1ID, 4, 1, file);
    fwrite(&data->subchunk1Size, 4, 1, file);
    fwrite(&data->audioFormat, 2, 1, file);
    fwrite(&data->nChannels, 2, 1, file);
    fwrite(&data->samplesRate, 4, 1, file);
    fwrite(&data->byteRate, 4, 1, file);
    fwrite(&data->blockAlign, 2, 1, file);
    fwrite(&data->bitsPerSample, 2, 1, file);
    fwrite(&data->subchunk2ID, 4, 1, file);
    fwrite(&data->subchunk2Size, 4, 1, file);

    for (int i = 0; i < data->subchunk2Size/2; i++) 
    {
        short sign = data->data[i] >= 0 ? 1 : -1;
        data->data[i] = (short)floor(pow(10, (20.*log10(abs(data->data[i]))+change_dB)/20.)) * sign;
    }

    fwrite(data->data, 2, data->subchunk2Size/2, file);

    fclose(file);
    return;
}

int main()
{
    setlocale(0, "");

    WavData header;
    // readWav виведет 1 если при чтении произойдёт ошибка
    if (readWav(&header, "Master Of Puppets.wav")){
        return 1;   
    }
    
    // Выводим полученные данные
    printf("\n  Заголовок WAV-файла\n-------------------------------------------------\n");
    printf(" Инфо о формате: %s\n", header.chunkID);
    printf(" Размер файла (начиная с этой позиции): %u\n", header.chunkSize);
    printf(" Формат данных: %s\n", header.format);
    printf(" Параметы WAV-файла: %s\n", header.subchunk1ID);
    printf(" Размер подчанка: %u\n", header.subchunk1Size);
    printf(" Формат аудио: %d\n", header.audioFormat);
    printf(" Количество каналов: %d", header.nChannels);
    if (header.nChannels == 2)
    {   printf(" => Стерео \n"); }
    else
    {   printf(" => Моно \n"); }

    printf(" Частота: %u\n", header.samplesRate);
    printf(" Байт в секунду: %u\n", header.byteRate);
    printf(" Размер blockAlign: %d\n", header.blockAlign);
    printf(" Размер сэмпла (кол-во бит в сэмпле): %d\n", header.bitsPerSample);
    printf(" Subchunk2ID: %s\n", header.subchunk2ID);
    printf(" Размер data: %u\n", header.subchunk2Size);

    // Длительность воспроизведения в минутах и секундах
    float fDurationSeconds = 1.f * header.chunkSize / (header.bitsPerSample / 8) / header.nChannels / header.samplesRate;
    int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
    fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
    printf(" Продолжительность аудио: %d.%d\n", iDurationMinutes, (int)fDurationSeconds);

    writeWav(&header, "Master Of Puppets edit.wav", -6);

    free(header.data);
    return 0;
}
