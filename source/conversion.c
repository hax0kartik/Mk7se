#include "libs.h"
uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

char hexToAscii(char first, char second)
 {

   char hex[5], *stop;

    hex[0] = '0';

    hex[1] = 'x';

    hex[2] = first;

    hex[3] = second;

    hex[4] = 0;
    
	return strtol(hex, &stop, 16);

}
uint16_t swap_uint16( uint16_t val ) 
  {
    return (val << 8) | (val >> 8 );
  }
	
char* dtohex(int decimalNumber) 
    {
    char* b=malloc(sizeof(char*));
    sprintf(b,"0x%X",decimalNumber);
    return b;
	}
char* iha(int a){
	       char* c;
			char d[10];
			uint32_t jk=0;
			uint32_t jm;
			
			c=dtohex(a);
			int j=0;
			puts(c);
			sscanf(c,"%X",&jm);
			if(a>15)
			jk=swap_uint32(jm);
		   
			char*convcoin=malloc(sizeof(char*));
            sprintf(convcoin, "%X", jk); 
			for(int jw=0;jw<5;jw++)
			{
				char a=hexToAscii(convcoin[jw],convcoin[jw+1]);
				//printf("%c",a);
				d[j]=a;
				j++;
				jw++;
			
			}
			free(convcoin);
			//printf("j:%d\n",j);
			d[j]='\0';
			//printf("%s",d);
			char *jf=malloc(sizeof(d));
			strcpy(jf,d);
		    return jf;
			
}	