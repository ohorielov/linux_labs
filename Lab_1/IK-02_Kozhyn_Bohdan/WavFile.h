#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


    struct WAVHEADER 
    {
    char chunkId[4];

    uint32_t chunkSize;
    
    char format[4];
    
    char subchunkId1[4];
    
    uint32_t subchunkSize1;
    
    uint8_t audioFormat;
    
    uint16_t numChannels;
    
    uint32_t sampleRate;
    
    uint32_t byteRate;
    
    uint8_t blockAlign;
    
    uint16_t bitsPerSample;
    
    char subchunkId2[4];
    
    uint32_t subchunkSize2;
    
    uint16_t data;

} wh;
