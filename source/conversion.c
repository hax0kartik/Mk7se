#include "libs.h"
void splitByte(uint8_t * split, unsigned int num)
{
	int i =0;
	while (num > 0){
		split[i]= num & 0xff;
		num = num >> 8;
		i++;
	}
	split[i] = '\0';
}