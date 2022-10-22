#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Macroses.h"

const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t BYTE2;

class WavHandler
{
public:
    WavHandler() = default;
    ~WavHandler() = default;
    
    int ScaleVolume(const char* inputFileName, 
                    const char* outputFileName, 
                    float scaleFactor);
};
