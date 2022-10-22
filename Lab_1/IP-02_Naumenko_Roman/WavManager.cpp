#include "WavManager.h"

WavManager::WavManager()
{};

WavManager::~WavManager()
{}

void WavManager::IncreaseVolume(const std::string& inputFileName, const std::string& outputFileName)
{
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    outputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        inputFile.open(inputFileName, std::ios::binary);
        outputFile.open(outputFileName, std::ios::binary);

        // reading data
        data = std::make_unique<std::vector<char>>( std::istreambuf_iterator<char>(inputFile), 
                                                    std::istreambuf_iterator<char>());

        if(data == nullptr)
            DebugLog("Failed to read file.");
        else if(data->size() == 0)
            DebugLog("File is empty");

        // reading file header
        std::memcpy((char*)&fileHeader, data->data(), sizeof(fileHeader));
        InfoLog(fileHeader);

        // processing data
        if (ProcessData())
            DebugLog("An error occured while processing data.");

        // writing data 
        std::copy( 
            data->begin(), 
            data->end(),
            std::ostreambuf_iterator<char>(outputFile));
        
        inputFile.close();
        outputFile.close();
    }
    catch (std::ifstream::failure& e)
    {
        DebugLog(e.what());
    }
}

int WavManager::ProcessData()
{
    return 0;
}

// FileHeader stuff
#if DEBUG
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
#endif //DEBUG
