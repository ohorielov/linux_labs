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
#include <filesystem>
#include "common.h"

WAVProcessor::WAVProcessor(WAVReader& wavReader)
: m_wavReader(std::move(wavReader))
{

}

void WAVProcessor::CopyAndChangeVolume(float multiplier)
{
    const std::filesystem::path path { m_wavReader.m_fileName };

    auto newFileName { path.parent_path().string() + common::GetSeparator() + std::string { "(changed)" } + path.filename().string() };
    auto newFilePtr { std::fopen(newFileName.c_str(), "w") };

    // writing header
    std::fwrite(&m_wavReader.m_wavHeader.RIFF, sizeof(WAVHeader), size_t{1}, newFilePtr);

    for (int i = 0; i < m_wavReader.m_wavHeader.Subchunk2Size; ++i)
    {
        std::int16_t sample = m_wavReader.m_sampleData[i];
        sample += static_cast<std::int16_t>(sample * multiplier);
        m_wavReader.m_sampleData[i] = sample;
    }

    std::fwrite(m_wavReader.m_sampleData, m_wavReader.m_wavHeader.Subchunk2Size, size_t{1}, newFilePtr);

    std::fclose(newFilePtr);
}