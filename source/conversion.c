#include "libs.h"
void splitByte(u8* split, unsigned int num)
{
	int i =0;
	while (num > 0){
		split[i]= num & 0xff;
		num = num >> 8;
		i++;
	}
}
void patchByte(char *data, unsigned int num, int offset)
{
	u8* split = malloc(sizeof(u8));
	memset(split,'\0',4);
	splitByte(split, num);
	for(int i=0; i<=3;i++)
	{
		data[offset+i] = 0x0;
	}	
	for(int i=0;split[i]!= '\0' ; i++)
	{
		data[offset+i] = split[i];
	}
	free(split);
}