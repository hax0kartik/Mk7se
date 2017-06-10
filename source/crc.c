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
	uint32_t v32 = ~0;
	uint8_t new[4];
	v32 = crc32_calc((u8*)j,20688, v32);
	splitByte(new,v32);
	j[BUFFER] = new[0];
	j[BUFFER+1] = new[1];
	j[BUFFER+2] = new[2];
	j[BUFFER+3] = new[3];
}