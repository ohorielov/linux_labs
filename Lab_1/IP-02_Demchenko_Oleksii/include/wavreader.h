//
// Created by h1lary on 25.09.22.
//

#ifndef IP_02_DEMCHENKO_OLEKSII_WAVREADER_H
#define IP_02_DEMCHENKO_OLEKSII_WAVREADER_H
#include "wav.h"
#include <cstdint>
#include <string>

class WAVReader
{
    WAVHeader m_wavHeader;
    FILE *m_filePtr;
    std::int16_t* m_sampleData;
    std::string m_fileName;
    std::uint64_t m_headerSize;
    std::uint16_t m_bytesPerSample;
    std::uint64_t m_numSamples;
    void Read();

    friend class WAVProcessor;

public:
    WAVReader(const std::string &fileName);
    WAVReader(const WAVReader&) = delete;
    WAVReader(WAVReader&& wavReader) noexcept;
    ~WAVReader();
    void OutputHeaderInfo() const;
    WAVHeader GetHeader() const;
    std::uint16_t GetBytesPerSample() const;
    std::uint64_t GetNumOfSamples() const;
};

#endif//IP_02_DEMCHENKO_OLEKSII_WAVREADER_H
