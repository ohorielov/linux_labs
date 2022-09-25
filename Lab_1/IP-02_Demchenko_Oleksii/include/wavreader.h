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
    std::uint64_t m_headerSize;
    void Read(std::uint64_t count);
    void Read();
    bool CheckIfFileExists(const std::string &fileName);

public:
    WAVReader(const std::string &fileName);
    ~WAVReader();
    void OutputHeaderInfo();
};

#endif//IP_02_DEMCHENKO_OLEKSII_WAVREADER_H
