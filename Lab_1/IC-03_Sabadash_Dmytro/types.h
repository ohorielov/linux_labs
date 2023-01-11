struct WavHeaderInBytes {
    unsigned char
            chunkSize[4],
            subChunk1Size[4],
            audioFormat[2],
            numChannels[2],
            sampleRate[4],
            byteRate[4],
            blockAlign[2],
            bitsPerSample[2],
            subChunk2Size[4];
};

struct WavHeader {
    unsigned int
            chunkSizeInt,
            subChunk1SizeInt,
            audioFormatInt,
            numChannelsInt,
            sampleRateInt,
            byteRateInt,
            blockAlignInt,
            bitsPerSampleInt,
            subChunk2SizeInt;
};

