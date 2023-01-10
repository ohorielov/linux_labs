#include "WavFile.c"


int main()
{

    FILE* input = fopen("Master Of Puppets.wav", "r");
    if (input == NULL)
    {
        printf("Can't open source file\n");
    }
    FILE* output = fopen("Master Of Puppets(modified).wav", "wb");
    fread(&wh, sizeof(wh), sizeof(wh), input);
    
    
    char wantdata;
    int i = 0;
    do
    {
    	
    	printf("Want to see Wav data?(y/n)\n");
    	scanf("%c", &wantdata);
    	switch(wantdata)
    	{
    	    case 'y': printWavData(wh); i = 1; break;
    	    
    	    case 'n': i = 1; break;
    	    
    	    default: system("clear"); i = 0; printf("Wrong choise, only y or n\n");
    	}
    	
    }while(i == 0);
    
   
    fwrite(&wh, sizeof(wh), sizeof(wh), output);
    
    modifyVolume(input, output);

    fclose(input);
    fclose(output);

}
