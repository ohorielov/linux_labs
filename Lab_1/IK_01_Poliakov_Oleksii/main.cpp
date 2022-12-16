#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdint>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using namespace std;


typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} WavHeader;

typedef struct WAV_METADATA {
    WavHeader* header;
    int filelength;
} WavMetadata;

// Function prototypes
int getFileSize(FILE* inFile);
WavMetadata readFileMetadata(char* filePath);

int main()
{
	char* FILE_NAME = getenv("FILE_NAME");
    if (FILE_NAME == NULL)
    {
        cout << "FILE_NAME is not defined" << endl;
        return 0;
    }
    else
    {
        cout << "FILE_NAME = " << FILE_NAME << endl;
    }

    readFileMetadata(FILE_NAME);
    // TODO: add file data reading
    // TODO: add file data volume changing
}

void printWavHeader (WavHeader wavHeader) {
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
    // uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      
    //Number     of bytes per sample
    // uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample; 
    //How many samples are in the wav file?
}

WavMetadata readFileMetadata(char* filePath)
{
    WavHeader wavHeader;
    int headerSize = sizeof(WavHeader), filelength = 0;

    FILE* wavFile = fopen(filePath, "r");
    if (wavFile == nullptr)
    {
        throw invalid_argument("Unable to open wav file");
    }

    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    if (bytesRead != sizeof wavHeader) {
        throw invalid_argument("Unable to read wav file header");
    }

    //TODO: move file data reading to separate function
    static const uint16_t BUFFER_SIZE = 4096;
    int8_t* buffer = new int8_t[BUFFER_SIZE];
    while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
    {
        /** DO SOMETHING WITH THE WAVE DATA HERE **/
        cout << "Read " << bytesRead << " bytes." << endl;
    }
    delete [] buffer;
    buffer = nullptr;
    
    fclose(wavFile);
    WavMetadata metadata;
    metadata.header = &wavHeader;
    metadata.filelength = getFileSize(wavFile);
    return metadata;
}

// find the file size
int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}