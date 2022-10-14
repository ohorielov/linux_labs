#include "my_lib.h"

#define CHUNK_NUMBER_STRIDE 2
#define MUSIC_FREQ_STRIDE 4
#define CHUNK_ID_SIZE 4
#define CHUNK_SIZE_FLD 4
#define BPS_STRIDE 14

char update_data(work_mode mode,sub_chunk* wav_file){
	uint16_t bps;
	uint32_t freq;
	memcpy(&bps,wav_file[0].data+BPS_STRIDE,sizeof(uint16_t));
	memcpy(&freq,wav_file[0].data+MUSIC_FREQ_STRIDE,sizeof(uint32_t));
	bps/=8;
	float* par;
	switch(mode){
		//multiplies
		case MULTIPLY:
			par = malloc(sizeof(float));
			printf("Enter multiplier[0.1:10]:");
			scanf("%f",par);
			if(!(par[0]>=0.1 && par[0]<=10))
				return 1;
		break;
		//adds absolute value
		case ADD:
			par = malloc(sizeof(float));
			printf("Enter add value[0:65535]:");
			scanf("%f",par);
			if(!(par[0]>=0 || par[0]<=65535))
				return 1;
		break;
		//trembling effect
		case TREMBLE:
			par = calloc(2,sizeof(float));
			printf("Enter amplitude[0:65535]:");
			scanf("%f",par);
			printf("Enter frequency(>0):");
			scanf("%f",par+1);
			if(!(par[0]>=0 && par[0]<=65535))
				return 1;
			if(par[1]<0)
				return 1;
		break;
		default:
			printf("%d - wrong mode!\n",mode);
			return 1;
	}
	int16_t* samp_data=malloc(bps);
	//wav_file[1].chunkSize-размер сегмента чанка с данными  bps - байт на сэмпл
	for(unsigned long int i =0 ;i<=wav_file[1].chunkSize;i+=bps){
		memcpy(samp_data,wav_file[1].data+i,bps);
		switch(mode){
			case MULTIPLY:
				*samp_data=(int16_t)*samp_data*par[0];
			break;

			case ADD:
				*samp_data=(int16_t)*samp_data+par[0];
			break;
			case TREMBLE:
				*samp_data=*samp_data+(int16_t)par[0]*sin(par[1]*2*3.1415926*(double)(i/bps/2 %freq)/freq);
			break;
		}
		memcpy(wav_file[1].data+i,samp_data,bps);
	}
	free(par);
	free(samp_data);
}

char read_wav(const char* filename){
//	printf("Attempt to open file:%s\n",filename);
	FILE* to_rd= fopen(filename,"r");
	if(!to_rd){
		printf("Can`t open file:%s\n",filename);
		return 1;
	}
	//declare 2 sub chunks since one goes to store header and second to data
	sub_chunk* wav_file= calloc(2,sizeof(sub_chunk));
	uint32_t ch_header[3];
	//skip header of main chunk by reading it
	fread(ch_header,sizeof(uint32_t),1,to_rd);
	fread(ch_header+1,sizeof(uint32_t),1,to_rd);
	fread(ch_header+2,sizeof(uint32_t),1,to_rd);
	//read subchunks data
	char readed;
	for(char i =0;i<2;i++){
		printf("reading chunk#%d\n",i);
		fread(&wav_file[i].chunkID,CHUNK_ID_SIZE,1,to_rd);
		fread(&wav_file[i].chunkSize,CHUNK_SIZE_FLD,1,to_rd);
		printf("Chunk size:%d|read:",wav_file[i].chunkSize);	wav_file[i].data=malloc(wav_file[i].chunkSize-4);
		readed = fread(wav_file[i].data,wav_file[i].chunkSize,1,to_rd);
		printf("%d\n",readed);
	}
	//chunk 0-metadata 1-music data
	uint16_t ch_num,bps;
	uint32_t s_r;
	memcpy(&ch_num,wav_file[0].data+CHUNK_NUMBER_STRIDE,sizeof(uint16_t));
	memcpy(&bps,wav_file[0].data+BPS_STRIDE,sizeof(uint16_t));
	memcpy(&s_r,wav_file[0].data+MUSIC_FREQ_STRIDE,sizeof(uint32_t));
	bps/=8;
	printf("Channel number:%d\nSample rate:%d\nBytes per sample:%d\n",ch_num,s_r,bps);
	FILE* to_wr = fopen("result.wav","w");
	fwrite(ch_header,sizeof(ch_header),1,to_wr);
	char to_d,ext=1;
	while(ext==1){
	printf("Enter edit mode:\n0-relative amplification\n1-absolute amplification\n2-trembling\n");
	scanf("%d",&to_d);
	ext=update_data(to_d,wav_file);
	}
	for(char i =0 ;i<2;i++){
		fwrite(&wav_file[i].chunkID,4,1,to_wr);
		fwrite(&wav_file[i].chunkSize,4,1,to_wr);
		readed = fwrite(wav_file[i].data,wav_file[i].chunkSize,1,to_wr);
		printf("Write info(chunk#%d):%d\n",i,readed);
	}
	fclose(to_wr);
	for(int i=0;i<2;i++)
		free(wav_file[i].data);
	free(wav_file);
	fclose(to_rd);
	printf("Closing");
	return 0;
}
