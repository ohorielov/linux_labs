#include "WavHandler.h"

int WavHandler::ScaleVolume(const char* inputFileName, 
                            const char* outputFileName, 
                            float scaleFactor)
{
    FILE *input = fopen(inputFileName, "r");
    FILE *output = fopen(outputFileName, "w");
    BYTE header[HEADER_SIZE];

    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    BYTE2 sample;

    while(fread(&sample, sizeof(BYTE2), 1, input))
    {
        sample *= scaleFactor;
        fwrite(&sample, sizeof(BYTE2), 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}