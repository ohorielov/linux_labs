#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using namespace std;

typedef struct WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t RIFF[4];    // RIFF Header Magic header
    uint32_t ChunkSize; // RIFF Chunk Size
    uint8_t WAVE[4];    // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t fmt[4];         // FMT header
    uint32_t Subchunk1Size; // Size of the fmt chunk
    uint16_t AudioFormat;   // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t NumOfChan;     // Number of channels 1=Mono 2=Sterio
    uint32_t SamplesPerSec; // Sampling Frequency in Hz
    uint32_t bytesPerSec;   // bytes per second
    uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo
    uint16_t bitsPerSample; // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t Subchunk2ID[4]; // "data"  string
    uint32_t Subchunk2Size; // Sampled data length
} WavHeader;

typedef struct WAV_METADATA
{
    WavHeader* header;
    uint16_t bytesPerSample;
    uint64_t samplesCount;
} WavMetadata;

typedef struct WAV_PARSED
{
    WavMetadata* metadata;
    int16_t *data;
} WavParsed;

// Function prototypes
void printWavHeader(WavHeader* wavHeader);
WavHeader* readFileHeader(FILE *wavFile);
int16_t *readFileData(FILE *wavFile, WavMetadata* metadata);
WavParsed readFile(char *fileName);
void writeFile(char *filePath, WavParsed parsed);
void updateFileData(int16_t *wavData, WavMetadata* metadata, double k);
void freeWavParsed(WavParsed parsed);

int main()
{
    const char *env_var[3] = {"FILE_NAME", "NEW_FILE_NAME", "VOLUME_K"};
    const char *default_env_val[3] = {"../Master Of Puppets.wav", "new.wav", "0.5"};
    char *env_val[3] = {};

    for (int i = 0; i < 3; i++)
    {
        char *val = getenv(env_var[i]);
        if (val != NULL)
        {
            cout << "Variable = " << env_var[i] << ", Value= " << val << endl;
            env_val[i] = val;
        }
        else
        {
            cout << env_var[i] << " doesn't exist, using default Value= " << default_env_val[i] << endl;
            env_val[i] = (char *)default_env_val[i];
        }
    }
    char *FILE_NAME = env_val[0];
    char *NEW_FILE_NAME = env_val[1];
    double k = stod(env_val[2]);
    if (k < 0.1 || k > 1.5)
    {
        throw invalid_argument("VOLUME_K is out of scope");
    }
    WavParsed parsed = readFile(FILE_NAME);
    // printWavHeader(*parsed.metadata->header);
    updateFileData(parsed.data, parsed.metadata, k);
    writeFile(NEW_FILE_NAME, parsed);
    freeWavParsed(parsed);
}

void printWavHeader(WavHeader wavHeader)
{
    cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
    cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
    cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
    cout << "Data size                  :" << wavHeader.ChunkSize << endl;

    // Display the sampling Rate from the header
    cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
    cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
    cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
    cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
    cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
    cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

    cout << "Block align                :" << wavHeader.blockAlign << endl;
    cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
}

WavHeader* readFileHeader(FILE *wavFile)
{
    WavHeader* wavHeader = (WavHeader*)malloc(sizeof(WavHeader));
    int headerSize = sizeof(WavHeader), filelength = 0;

    if (wavFile == nullptr)
    {
        throw invalid_argument("Unable to open wav file");
    }

    // Read the header
    size_t bytesRead = fread(wavHeader, 1, headerSize, wavFile);
    if (bytesRead != sizeof *wavHeader)
    {
        throw invalid_argument("Unable to read wav file header");
    }
    return wavHeader;
}

int16_t *readFileData(FILE *wavFile, WavMetadata* metadata)
{
    int16_t *wavData = new int16_t[metadata->samplesCount];
    size_t f = fread(wavData, metadata->bytesPerSample, metadata->samplesCount, wavFile);
    return wavData;
}

void updateFileData(int16_t *wavData, WavMetadata* metadata, double k)
{
    int i = 0;
    while (i < metadata->samplesCount)
    {
        wavData[i] = (int16_t)(wavData[i] * k);
        i++;
    }
}

void writeHeader(FILE *wavFile, WavMetadata* metadata)
{
    fwrite(metadata->header, sizeof(WavHeader), 1, wavFile);
}

void writeFileData(FILE *wavFile, int16_t *wavData, WavMetadata* metadata)
{
    fwrite(wavData, metadata->bytesPerSample, metadata->samplesCount, wavFile);
}

void writeFile(char *filePath, WavParsed parsed)
{
    FILE *wavFile = fopen(filePath, "wb");
    writeHeader(wavFile, parsed.metadata);
    writeFileData(wavFile, parsed.data, parsed.metadata);
    fclose(wavFile);
}

WavParsed readFile(char *filePath)
{
    FILE *wavFile = fopen(filePath, "rb");
    WavHeader* wavHeader = readFileHeader(wavFile);
    uint16_t bytesPerSample = wavHeader->bitsPerSample / 8;
    uint64_t numSamples = wavHeader->ChunkSize / bytesPerSample;
    WavMetadata* metadata = (WavMetadata*)malloc(sizeof(WavMetadata));
    metadata->header = wavHeader;
    metadata->bytesPerSample = bytesPerSample;
    metadata->samplesCount = numSamples;
    int16_t *wavData = readFileData(wavFile, metadata);
    fclose(wavFile);
    WavParsed parsed;
    parsed.metadata = metadata;
    parsed.data = wavData;
    return parsed;
}

void freeWavParsed(WavParsed parsed)
{
    free(parsed.metadata->header);
    free(parsed.metadata);
    free(parsed.data);
}