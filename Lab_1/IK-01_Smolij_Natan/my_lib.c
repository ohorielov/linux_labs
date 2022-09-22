#include "my_lib.h"

void say(const char* to_say)
{
	printf(to_say);
}

wav_header* read_wav(const char* filename)
{
	printf("Attempt to open file:%s\n",filename);
	FILE* to_rd= fopen(filename,"r");
	if(to_rd==NULL)
	{
		printf("Can`t open file:%s\n",filename);
		return NULL;
	}

	sub_chunk* wav_file= calloc(2,sizeof(sub_chunk));
	uint32_t ch_id;
	//skip header of main chunk
	fread(&ch_id,sizeof(ch_id),1,to_rd);
	fread(&ch_id,sizeof(ch_id),1,to_rd);
	fread(&ch_id,sizeof(ch_id),1,to_rd);
	//read subchunks data
	for(int i =0;i<2;i++)
	{
		printf("reading chunk#%d\n",i);
		fread(&wav_file[i].chunkID,4,1,to_rd);
		fread(&wav_file[i].chunkSize,4,1,to_rd);
		printf("Chunk size:%d\n",wav_file[i].chunkSize);
		wav_file[i].data=malloc(wav_file[i].chunkSize-4);
		fread(wav_file[i].data,wav_file[i].chunkSize-4,1,to_rd);
	}
	//chunk 0-metadata 1-music data
	uint8_t ch_num,bps,s_r;
	memcpy(&ch_num,wav_file[0].data+2,2);
	memcpy(&bps,wav_file[0].data+14,2);
	memcpy(&s_r,wav_file[0].data+4,4);
	bps/=8;
	printf("Channel number:%d\nSample rate:%d\nBytes per sample:%d\n",ch_num,s_r,bps);
	printf("Closing");
	for(int i=0;i<2;i++)
	{
		free(wav_file[i].data);
	}
	free(wav_file);
	fclose(to_rd);
}
