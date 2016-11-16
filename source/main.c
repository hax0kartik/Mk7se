#include "libs.h"
#define entry 9
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */
#include <time.h>


/*Result trySave(FS_Archive *out, u64 id) {
	bool ret = false;
	u32 path[3] = {MEDIATYPE_GAME_CARD, id, id >> 32};
	Result res = FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, path});
	if (res) {
		//Try SD
		Result res=0;
		u32 path[3] = {MEDIATYPE_SD, id, id >> 32};
		res = FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, path});
		if (res)
			ret = 1;
		else
			ret = 0;
		return ret;
	}*/
	
	/*
	else
		ret = true;

	return ret;
}*/

/* CRC-32, eg. ethernet */

void make_b(char fg[],char g[])
 {       char af[]="/mk7se/backup";
         char ad[400];
		 puts("going to make a backup");
		 char *ah=rfds(fg);
		 char *gh=rfds(g);
		 puts("File read successful");
        if(!(mkdir(af , 0777)))
			printf("backup path made with success\n");
        else 
			printf("fail");
	    time_t unixTime = time(NULL);
		struct tm* timeStruct = gmtime((const time_t *)&unixTime);
        char az[20];
		int hours = timeStruct->tm_hour;
		int minutes = timeStruct->tm_min;
        int day = timeStruct->tm_mday;
		printf("/%i_%02i_%02i\n",day,hours, minutes);
        sprintf(az,"/%i_%02i_%02i",day,hours, minutes);
		puts(az);
		strcat(af,az);
		printf("path 1: %s\n",af);
		puts(af);
	    memmove (fg, fg+6, 11);
		memmove (g,g+6,11);
		 
		 puts(fg);
		 puts(g);
		if(!(mkdir(af , 0777)))
			printf("backup path2 created\n");
		  
	    strcpy(ad,af);
		printf("ad:%s\n",ad);
		strcat(ad,(const char*)fg);
		puts(ad);
		strcat(af,(const char*)g);
		puts(af);
		FILE *f = fopen(af, "wb+");
           fwrite(ah, 1, strlen(ah), f);
           fclose(f);
        f = fopen(ad, "wb+");
           fwrite(ah, 1, strlen(ah), f);
           fclose(f);
}


void draw(int curent, char *menu[], int N,PrintConsole *top,PrintConsole*bottom) {
	consoleSelect(top);
	printf("\x1b[10;0H\x1b[30;0m");
	for (int i = 0; i < N; i++) {
		if (i == curent)
			printf("\x1b[31;1m* %s\x1b[0m\n", menu[i]);
		else
			printf("\x1b[0m* %s\n", menu[i]);
	}
	consoleSelect(bottom);
}

char *tl(SwkbdState swkbd ,char *texgen)
{        
            SwkbdButton button = SWKBD_BUTTON_NONE;
            swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 2, -1);
            swkbdSetHintText(&swkbd, texgen);
            swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
	        char mybuf[1024];
            button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
			int w=atoi(mybuf);
			printf("%d\n",w);
			char*jk=iha(w);
			return jk;	
}


int main()
{
    SwkbdState swkbd;
    char mybuf[960];
    //char loca[1024];
    SwkbdButton button = SWKBD_BUTTON_NONE;
    bool didit = false;
    bool didloc = false;
    char *menu[entry]={"Edit no of coins","Edit no of wins","Edit no of lose","Edit VR","Unlock all tracks","Unlock all chars",
	"Unlock all Karts","Unlock all tires","Unlock all gliders"};
	int curent = 0;
	    gfxInitDefault();
		PrintConsole top, bottom;
		consoleInit(GFX_TOP,&top);
		consoleInit(GFX_BOTTOM,&bottom);
		consoleSelect(&bottom);
		printf("Searching for game saves..");    
    //const u64 titles[3] = {0x0004000000030600, 0x0004000000030700,0x0004000000030800};	//japan,europe,US
	const u64 id=0x0004000000030700;
	u8* buf=malloc(sizeof(u8*));
    u64 bSize = 0;
	FS_Archive saveArch;
	Result ret=1;
	Result res=1;
	char*sys="/mk7se/system0.dat";
	char filez[100];
	char file[100];
	for(int x=0;x<10;x++)
	{   //printf("%d\n",x);
       // printf("%c\n",sys[28]);
		sprintf(file, "/mk7se/system%d.dat",x);
		res=file_exist(file);
		if(res==0)
		{
			puts("files found\n");
			printf("file1:%s\n",file);
			sprintf(filez, "/mk7se/system%d.dat",++x);
			printf("file2:%s\n",filez);
			break;
		}
	
}       
       
		make_b(file,filez);
	/*  
	ret=fsInit();
	uint8_t mediatype=0x01;
	FS_Archive *out=malloc(sizeof(FS_Archive*));
	u32 path[3] = {MEDIATYPE_SD ,mediatype, id>>32};
		res = FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, path});
       if(res < 0)
{
    printf("Error or not found: %08X\n", res);
}
     else
{
    puts("Okay");
}
 u32 path2[3] = {MEDIATYPE_SD ,1, id>>32};
		res = FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, path2});
       if(res < 0)
{
    printf("Error or not found: %08X\n", res);
}
     else
{
    puts("Okay");
}
u32 path3[3] = {MEDIATYPE_SD, 2, id>>32};
		res = FSUSER_OpenArchive(out, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, path3});
       if(res < 0)
{
    printf("Error or not found: %08X\n", res);
}
     else
{
    puts("Okay");
}
	  */
     //fsExit();
			//free (buf);
			//free(out);
	draw(curent,menu,entry,&top,&bottom);
    while (aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown = hidKeysDown();
		if(kDown & KEY_DUP)
		{
			if (curent==0){
				curent=entry-1;
				draw(curent,menu,entry,&top,&bottom);
			}
			else if (curent>0)
			{
				curent --;
				draw(curent,menu,entry,&top,&bottom);
			}
		}
		if(kDown & KEY_DDOWN)
		{
			if(curent == entry-1)
			{
				curent=0;
		      draw(curent,menu,entry,&top,&bottom);
			}
			else if (curent < entry-1)
			{
				curent++;
				draw(curent,menu,entry,&top,&bottom);
			}
				
			}
		
        if (kDown & KEY_A) {
           
		   switch(curent){
			   case 0:
			   {  printf("Coins changed to:");
			      char*dg=tl(swkbd,"Enter no. of coins");
				  wf(file,dg,COIN);
				  cal_save(file);
			      wf(filez,dg,COIN);
				  cal_save(filez);
			       break;
				  
		       }
			   case 1:
			   {  printf("Wins changed to:");
				  char*dg=tl(swkbd,"Enter no. of wins");
				  wf(file,dg,WIN);
				  cal_save(file);
			      wf(filez,dg,WIN);
				  cal_save(filez);
			       break;
			   }
			   case 2:
			   {   printf("Losses changed to:");
				  char*dg=tl(swkbd,"Enter no. of losses");
				  wf(file,dg,LOSE);
				  cal_save(file);
			      wf(filez,dg,LOSE);
				  cal_save(filez);
			      break;
				    
			    }		
               case 3:
			      {     
			      printf("Vr changed to:");
			      char*dg=tl(swkbd,"Enter the new VR");
				  wf(file,dg,VR);
				  cal_save(file);
			      wf(filez,dg,VR);
				  cal_save(filez);
			      break;
				
			      }	
               case 4:
		          {
			       printf("Unlocked all the tracks\n");
			       int a=63;
			       wf_c(file,a,TRACK);
			       wf_c(filez,a,TRACK);
			       cal_save(file);
			       cal_save(filez);
				   break;
		          }		 
               case 5:
		          {
		           int a=255;
		           int b=01;
			       wf_c(file,a,CHAR);
			       wf_c(file,b,CHAR+1);
			       wf_c(file,a,CHAR+2);
                   wf_c(file,b,CHAR+3);		
                   wf_c(filez,a,CHAR);
			       wf_c(filez,b,CHAR+1);
			       wf_c(filez,a,CHAR+2);
                   wf_c(filez,b,CHAR+3);				  
			       printf("Unlocked all chars\n");
			       cal_save(file);
			       cal_save(filez);
				   break;
		          }	
               case 6:
		          {
			       int a=255;//ff
			       int b=63;//3f
			       wf_c(file,a,KART);
			       wf_c(file,b,KART+1);
			       wf_c(filez,a,KART);
			       wf_c(filez,b,KART+1);
			       printf("Unlocked all karts\n");
			       cal_save(file);
			       cal_save(filez);
				   break;
			      }	
               case 7:
	              {
		           int a=127;//7f
		           wf_c(file,a,TIRE);
		           wf_c(filez,a,TIRE);
		           printf("Unlocked all tires\n");
		           cal_save(file);
		           cal_save(filez);
				   break;
	              }	   
	          case 8:
	              {
		           int a=63;//3f
		           wf_c(file,a,GLIDER);
		           wf_c(filez,a,GLIDER);
		           printf("Unlocked all gliders\n");
		           cal_save(file);
		           cal_save(filez);
			       break;
	   }
		   }
        
		}
        if (kDown & KEY_START)
            break;
        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();
    }
	free(buf);
    gfxExit();
    return 0;
}
