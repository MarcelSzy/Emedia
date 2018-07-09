#include <stdio.h>
#include <stdint.h>


struct Wav_header
{
	/* RIFF Chunk Descriptor */
  	uint8_t riff[4];			// RIFF Header Magic header
  	uint32_t chunksize;			// RIFF Chunk Size
  	uint8_t file_type[4];			// WAVE Header
  	/* "fmt" sub-chunk */
  	uint8_t format_chunk[4];		// FMT header
  	uint32_t fmt_chunk_size;		// Size of the fmt chunk
  	uint16_t audio_format_type;		// Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
  	uint16_t channel_number;		// Number of channels 1=Mono 2=Sterio
  	uint32_t samples_per_second;		// Sampling Frequency in Hz
  	uint32_t bytes_per_second;		// bytes per second
  	uint16_t audio_type;			// 2=16-bit mono, 4=16-bit stereo
  	uint16_t bytes_per_sample;		// Number of bits per sample
  	/* "data" sub-chunk */
  	uint8_t data[4];				// "data"  string
 	uint32_t data_length;			// Sampled data length*/
}hdr;
	
int main(int argc, char *argv[])
{
	FILE *file;
	file = fopen(argv[1], "rb");
	if(file != NULL){
		Wav_header header;
		int header_size=sizeof(header);
		fread(&header, header_size, 1, file);
		int file_length=sizeof(file);
		fread(&header.data_length, sizeof(unsigned int), 1, file);
		fclose(file);
		
		printf("RIFF: \t\t\t");
		for(int i=0; i<4; ++i)
		{
			printf("%c", header.riff[i]);
		}
		printf("\nRIFF Chunk Size:\t%i KB\n", header.chunksize/1024);
		printf("File type: \t\t");

		for(int i=0; i<4; ++i)
		{
			printf("%c", header.file_type[i]);
		}
		printf("\nFormat chunk: \t\t");

		for(int i=0; i<4; ++i)
		{
			printf("%c", header.format_chunk[i]);
		}
		printf("\nFMT chunk size: \t%i", header.fmt_chunk_size);

		printf("\nFormat type: \t\t");
		if(header.audio_format_type == 1)
		{
			printf("PCM");
		}
		else if (header.audio_format_type == 6)
		{
			printf("mulaw");
		}
		else if (header.audio_format_type == 7)
		{
			printf("alaw");
		}
		else if (header.audio_format_type == 257)
		{
			printf("IBM Mu-Law");
		}
		else if (header.audio_format_type == 258)
		{
			printf("IBM A-Law");
		}
		else if (header.audio_format_type == 259)
		{
			printf("ADPCM");
		}
		else
		{
			printf("UNKNOW");
		}
		printf("\nNumber of channels: \t%i", header.channel_number);
		printf("\nFrequency: \t\t%i Hz", header.samples_per_second);
		printf("\nBytes per second: \t%i", header.bytes_per_second);
		printf("\nAudio type: \t\t");
		if(header.audio_type == 2)
		{
			printf("mono");
		}
		else if(header.audio_type == 4)
		{
			printf("stereo");
		}
		else
		{
			printf("UNKNOW");
		}
		printf("\nBytes per sampele: \t%i", header.bytes_per_sample);
		printf("\nData: \t\t\t");
		for(int i=0; i<4; ++i)
		{
			printf("%c", header.data[i]);
		}
		printf("\n");
		printf("Data length: \t\t%i KB\n", header.data_length/1048576);
	}
	return 0;
}
