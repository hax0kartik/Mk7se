#include "libs.h"
void wf(char *loca,char *data,int pos){
		   FILE *f = fopen(loca, "rb+");
           fseek(f,pos,1);
           fwrite(data, 1, strlen(data), f);
           fflush(f);
           fclose(f);
}
void wf_c(char *loca,int d,int pos){
	  FILE *fp = fopen(loca, "r+");
      fseek (fp , pos, SEEK_SET);
      fputc(d, fp);
      fflush(fp);
      fclose(fp);	
}
char* rfds(char * loca)
{   char buffer[FILE_S];
    FILE* file = fopen(loca, "rb");
    if (file == NULL) {
        printf("File not found\n");
        fclose(file);
        //didloc = true;
    }
    else {
        fseek(file, 0, SEEK_END);
        off_t size = ftell(file);
        fseek(file, 0, SEEK_SET);
        //if(!buffer)
        //printf("error while allocating buffer\n");
        off_t bytesRead = fread(buffer, 1, size, file);

        fclose(file);
        if (size != bytesRead)
            printf("error");
		  
    }
	return buffer;
}
char *rf(char*loca,int offset,int len)
{   char *buffer=malloc(sizeof(char*));
    FILE* file = fopen(loca, "rb");
    if (file == NULL) {
        fclose(file);
        //didloc = true;
    }
    else {
        fseek(file,offset, SEEK_SET);
       
        //printf("error while allocating buffer\n");
	    
        off_t bytesRead = fread(buffer, 1, len, file);

        fclose(file);
        if (len != bytesRead)
            printf("error");
		
    }
    return buffer;   	
}
Result file_exist(char *f){
	Result ret=1;
	if(access((const char*)f,F_OK)!=-1)
	ret=0;
    else ret=1;
	return ret;
}