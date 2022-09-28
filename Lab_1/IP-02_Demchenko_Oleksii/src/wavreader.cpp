//
// Created by h1lary on 25.09.22.
//
#include <cstdio>
#include <iostream>
#include <string>

#include "common.h"
#include "except.h"
#include "wavreader.h"

WAVReader::WAVReader(const std::string &fileName)
    : m_headerSize(sizeof(WAVHeader)),
      m_bytesPerSample(0),
      m_numSamples(0),
      m_fileName(fileName),
      m_sampleData(nullptr)
{
    if (common::CheckIfFileExists(fileName))
    {
        throw pretty_expection(__PRETTY_FUNCTION__ + std::string(": file not found"));
    }

    m_filePtr = fopen(fileName.c_str(), "r");
    Read();
}

WAVReader::WAVReader(WAVReader &&wavReader) noexcept
    : m_wavHeader(wavReader.m_wavHeader),
      m_bytesPerSample(wavReader.m_bytesPerSample),
      m_filePtr(wavReader.m_filePtr),
      m_numSamples(wavReader.m_numSamples),
      m_headerSize(wavReader.m_headerSize),
      m_fileName(wavReader.m_fileName),
      m_sampleData(wavReader.m_sampleData)
{
    wavReader.m_wavHeader = WAVHeader();
    wavReader.m_bytesPerSample = 0;
    wavReader.m_filePtr = nullptr;
    wavReader.m_numSamples = 0;
    wavReader.m_headerSize = 0;
    wavReader.m_fileName = "";
    wavReader.m_sampleData = nullptr;
}

WAVReader::~WAVReader()
{
    if (m_filePtr != nullptr)
        delete m_filePtr;
    if (m_sampleData != nullptr)
        delete[] m_sampleData;
}

void WAVReader::Read()
{
    size_t bytesRead{std::fread(&m_wavHeader, 1, m_headerSize, m_filePtr)};
    if (bytesRead < m_headerSize)
    {
        throw pretty_expection(__PRETTY_FUNCTION__ + std::string(": unexpected behavior while reading"));
    }

    m_sampleData = new std::int16_t[m_wavHeader.Subchunk2Size];
    fread(m_sampleData, m_wavHeader.Subchunk2Size, 1, m_filePtr);

    fclose(m_filePtr);
    m_filePtr = nullptr;
}

uint16_t WAVReader::GetBytesPerSample() const
{
    return m_bytesPerSample;
}

uint64_t WAVReader::GetNumOfSamples() const
{
    return m_numSamples;
}

WAVHeader WAVReader::GetHeader() const
{
    return m_wavHeader;
}

void WAVReader::OutputHeaderInfo() const
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
