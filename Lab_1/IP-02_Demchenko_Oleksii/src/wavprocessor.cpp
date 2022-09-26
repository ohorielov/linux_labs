//
// Created by h1lary on 27.09.22.
//
#include "wavprocessor.h"
#include <vector>
#include <stdio.h>
#include <fstream>
#include "wav.h"
#include <memory>
#include <cstring>

WAVProcessor::WAVProcessor(WAVReader& wavReader)
: m_wavReader(std::move(wavReader))
{

}

void WAVProcessor::CopyAndChangeVolume(float multiplier)
{
    const auto newFileName { m_wavReader.m_fileName + "(changed)" };
    auto newFilePtr { std::make_unique<FILE*>(std::fopen(newFileName.c_str(), "w")) };

    // writing header
    std::fwrite(&m_wavReader.m_wavHeader, sizeof(WAVHeader), size_t { 1 }, *newFilePtr);

    static const std::uint16_t bufferSize { 4096 };
    std::vector<char> buffer;
    buffer.resize(bufferSize);

    std::uint64_t bytesRead { 0 };
    while ((bytesRead = std::fread(&buffer, sizeof(buffer[0]), bufferSize / sizeof(buffer[0]), m_wavReader.m_filePtr)) > 0)
    {
        for (int i = 0; i < buffer.size(); ++i)
        {
            std::int64_t sample { 0 };
            for (int j = 0; j < m_wavReader.m_bytesPerSample; ++j)
            {
                sample = sample | buffer[i+j] << j * 8;
            }
            sample = static_cast<std::uint64_t>(sample * multiplier);
            std::fwrite(&sample, sizeof(m_wavReader.m_bytesPerSample), 1, *newFilePtr);
            i += m_wavReader.m_bytesPerSample - 1;
        }
    }
}