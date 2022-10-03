#include "WavManager.h"

WavManager::WavManager(const std::string& fileName)
{
    Open(fileName);
};

WavManager::~WavManager()
{
    Close();
}

void WavManager::Open(const std::string& fileName)
{
    std::string vertexCode;
    std::ifstream inputFile;

    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        inputFile.open(fileName, std::ios::binary);
        int numRead;

        if(!inputFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(WavManager::FileHeader)))
        {
            std::cout << "Failed to read file header" << std::endl;
            exit(3);
        }
        else
        {
            DebugLog(fileHeader);
        }
    }
    catch (std::ifstream::failure& e)
    {
        DebugLog(e.what());
    }
}

void WavManager::Close()
{
    std::cout << "File closed." << std::endl;
}

// FileHeader stuff
std::ostream& operator<< (std::ostream& out, const WavManager::FileHeader& fh)
{
    out << "/--RIFF Chunk Descriptor--/" << std::endl;
    out << "ChunkID: \t"        << fh.ChunkID[0]
                                << fh.ChunkID[1]
                                << fh.ChunkID[2]
                                << fh.ChunkID[3]
                                << std::endl;
    out << "ChunkSize: \t"      << fh.ChunkSize << std::endl;
    out << "Format: \t"         << fh.Format[0]
                                << fh.Format[1]
                                << fh.Format[2]
                                << fh.Format[3]
                                << std::endl;
    out << "/--\"fmt\" sub-chunk--/" << std::endl;
    out << "Subchunk1ID: \t"    << fh.Subchunk1ID[0]
                                << fh.Subchunk1ID[1]
                                << fh.Subchunk1ID[2]
                                << fh.Subchunk1ID[3]
                                << std::endl;
    out << "Subchunk1Size: \t"  << fh.Subchunk1Size << std::endl;
    out << "AudioFormat: \t"    << fh.AudioFormat << std::endl;
    out << "NumChannels: \t"    << fh.NumChannels << std::endl;
    out << "SampleRate: \t"     << fh.SampleRate << std::endl;
    out << "ByteRate: \t"       << fh.ByteRate << std::endl;
    out << "BlockAlign: \t"     << fh.BlockAlign << std::endl;
    out << "BitsPerSample: \t"  << fh.BitsPerSample << std::endl;
    out << "/--\"data\" sub-chunk--/" << std::endl;
    out << "Subchunk2ID: \t"    << fh.Subchunk2ID[0]
                                << fh.Subchunk2ID[1]
                                << fh.Subchunk2ID[2]
                                << fh.Subchunk2ID[3]
                                << std::endl;
    out << "Subchunk2Size: \t"  << fh.Subchunk2Size;
    return out;
}
