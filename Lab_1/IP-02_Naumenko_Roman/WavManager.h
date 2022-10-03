#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include "LogMacros.h"

class WavManager
{
public:
    struct FileHeader
    {
        /* RIFF Chunk Descriptor */
        uint8_t         ChunkID[4];     // RIFF Header Magic header
        uint32_t        ChunkSize;      // RIFF Chunk Size
        uint8_t         Format[4];      // WAVE Header
        /* "fmt" sub-chunk */
        uint8_t         Subchunk1ID[4]; // FMT header
        uint32_t        Subchunk1Size;  // Size of the fmt chunk
        uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
        uint16_t        NumChannels;    // Number of channels 1=Mono 2=Sterio
        uint32_t        SampleRate;     // Sampling Frequency in Hz
        uint32_t        ByteRate;       // bytes per second
        uint16_t        BlockAlign;     // 2=16-bit mono, 4=16-bit stereo
        uint16_t        BitsPerSample;  // Number of bits per sample
        /* "data" sub-chunk */
        uint8_t         Subchunk2ID[4]; // "data"  string
        uint32_t        Subchunk2Size;  // Sampled data length

        friend std::ostream& operator<< (std::ostream& out, const FileHeader& fh);
    };
public:
    WavManager(const std::string& fileName);
    ~WavManager();

    void Open(const std::string& fileName);
    void Close();
    bool IsOpen();

private:
    FileHeader fileHeader;
};