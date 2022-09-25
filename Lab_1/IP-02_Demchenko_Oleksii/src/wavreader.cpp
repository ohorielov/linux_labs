//
// Created by h1lary on 25.09.22.
//
#include "wavreader.h"
#include "except.h"
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

WAVReader::WAVReader(const std::string &fileName)
    : m_headerSize(sizeof(WAVHeader))
{
    if (CheckIfFileExists(fileName))
    {
        throw pretty_expection(__PRETTY_FUNCTION__ + std::string(": file not found"));
    }

    m_filePtr = fopen(fileName.c_str(), "r");
    Read();
}

WAVReader::~WAVReader()
{
    delete m_filePtr;
}

bool WAVReader::CheckIfFileExists(const std::string &fileName)
{
    const std::filesystem::path pathToFileName{fileName.c_str()};
    return !std::filesystem::exists(pathToFileName);
}

void WAVReader::Read()
{
    size_t bytesRead{std::fread(&m_wavHeader, 1, m_headerSize, m_filePtr)};
    if (bytesRead < m_headerSize)
    {
        throw pretty_expection(__PRETTY_FUNCTION__ + std::string(": unexpected behavior while reading"));
    }

    std::uint16_t bytesPerSample = m_wavHeader.bitsPerSample / 8;     //Number     of bytes per sample
    std::uint64_t numSamples = m_wavHeader.ChunkSize / bytesPerSample;//How many samples are in the wav file?
    static const std::uint16_t BUFFER_SIZE = 4096;
    auto *buffer = new int8_t[BUFFER_SIZE];
    while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), m_filePtr)) > 0)
    {
        /** DO SOMETHING WITH THE WAVE DATA HERE **/
        std::cout << "Read " << bytesRead << " bytes." << std::endl;
    }
    delete[] buffer;
    buffer = nullptr;



}

void WAVReader::Read(std::uint64_t count)
{
}

void WAVReader::OutputHeaderInfo()
{
    std::cout << "RIFF header                :" << m_wavHeader.RIFF[0] << m_wavHeader.RIFF[1] << m_wavHeader.RIFF[2] << m_wavHeader.RIFF[3] << std::endl;
    std::cout << "WAVE header                :" << m_wavHeader.WAVE[0] << m_wavHeader.WAVE[1] << m_wavHeader.WAVE[2] << m_wavHeader.WAVE[3] << std::endl;
    std::cout << "FMT                        :" << m_wavHeader.fmt[0] << m_wavHeader.fmt[1] << m_wavHeader.fmt[2] << m_wavHeader.fmt[3] << std::endl;
    std::cout << "Data size                  :" << m_wavHeader.ChunkSize << std::endl;

    // Display the sampling Rate from the header
    std::cout << "Sampling Rate              :" << m_wavHeader.SamplesPerSec << std::endl;
    std::cout << "Number of bits used        :" << m_wavHeader.bitsPerSample << std::endl;
    std::cout << "Number of channels         :" << m_wavHeader.NumOfChan << std::endl;
    std::cout << "Number of bytes per second :" << m_wavHeader.bytesPerSec << std::endl;
    std::cout << "Data length                :" << m_wavHeader.Subchunk2Size << std::endl;
    std::cout << "Audio Format               :" << m_wavHeader.AudioFormat << std::endl;
    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

    std::cout << "Block align                :" << m_wavHeader.blockAlign << std::endl;
    std::cout << "Data string                :" << m_wavHeader.Subchunk2ID[0] << m_wavHeader.Subchunk2ID[1] << m_wavHeader.Subchunk2ID[2] << m_wavHeader.Subchunk2ID[3] << std::endl;
}