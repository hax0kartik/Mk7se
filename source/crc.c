#include "libs.h"
const uint32_t crc32_tbl[] = {

0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c


};
/* the idea is to act on nybbles instead of bytes to require less CPU cache */
uint32_t crc32_calc(uint8_t *ptr, int cnt, uint32_t crc)
{
	while (cnt--) {
		crc = (crc >> 4) ^ crc32_tbl[(crc & 0xf) ^ (*ptr & 0xf)];
		crc = (crc >> 4) ^ crc32_tbl[(crc & 0xf) ^ (*(ptr++) >> 4)];
	}
	return crc;
}
void cal_save(char* j)
{
	
   FILE *fp;
  
   char * buffer;

   int len;
	uint32_t v32 = ~0;
	FILE *f;

		f = fopen(j, "rb+");
		
		len = fread(msg, 1, BUFFER, f);
		
		if (ferror(f)) {
			puts("error");
			
		}
		v32 = crc32_calc(msg, len, v32);
	

	fclose(f);
	char str[10];
	char hexed[4];
	uint32_t swapped =swap_uint32(~v32);
    snprintf(str, sizeof str, "%08lX", (unsigned long)swapped); 
            
          char a=hexToAscii(str[0],str[1]);      

		  hexed[0]=a;
		   int z=1;
		   for(int i=2;i<=7;i++)
			{
				char b=hexToAscii(str[i],str[i+1]);
				i++;
				hexed[z++]=b;	
			}
	hexed[4]='\0';
   
   fp = fopen(j,"rb+");
   fseek(fp,20688,1);
   fwrite(hexed, 1, 4, fp);
   fflush(fp);
   
   fclose(fp);
}