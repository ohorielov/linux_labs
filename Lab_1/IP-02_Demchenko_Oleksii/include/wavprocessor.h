//
// Created by h1lary on 27.09.22.
//

#ifndef IP_02_DEMCHENKO_OLEKSII_WAVPROCESSOR_H
#define IP_02_DEMCHENKO_OLEKSII_WAVPROCESSOR_H
#include "wavreader.h"

class WAVProcessor
{
    WAVReader m_wavReader;

public:
    WAVProcessor(WAVReader &wavReader);
    WAVProcessor(const WAVProcessor &) = delete;
    WAVProcessor(WAVProcessor &&) = delete;
    ~WAVProcessor() = default;
    void CopyAndChangeVolume(float multiplier);
};

#endif//IP_02_DEMCHENKO_OLEKSII_WAVPROCESSOR_H
