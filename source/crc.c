#include "libs.h"
unsigned int crc32b(unsigned char *message) {
   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;
   while (i!= 20688) {
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}

void cal_save(char* buf)
{
	unsigned int v32 = 0;
	u8 *new = malloc(sizeof(u8*)*2); 
	v32 = crc32b(buf);
	splitByte(new,v32);
	buf[BUFFER] = new[0];
	buf[BUFFER+1] = new[1];
	buf[BUFFER+2] = new[2];
	buf[BUFFER+3] = new[3];
}