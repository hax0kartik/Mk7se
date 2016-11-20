#include "libs.h"
#define entry 9
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */
#include <time.h>

/* CRC-32, eg. ethernet */

Result make_b(char *fg,int b)
 {       
         FILE *fp1, *fp2;
         char ch;
         char az[1024];
		 printf("%d",b);
		 int pos;
		 if(!(mkdir("/mk7se/backup", 0777)))
		 {
			 puts("backup folder created");
		 }
		time_t unixTime = time(NULL);
		struct tm* timeStruct = gmtime((const time_t *)&unixTime);

		int hours = timeStruct->tm_hour;
		int minutes = timeStruct->tm_min;
        int day = timeStruct->tm_mday;
		
       char ag[20];
       sprintf(az,"/mk7se/backup/%i_%02i_%02i",day,hours, minutes);
         if(!(mkdir(az, 0777)))
		 {
			 puts("backup folder created");
		 }
    sprintf(ag,"/system%d.dat",b);
    strcat(az,ag);

    fp1 = fopen(fg, "rb");
	if(fp1==NULL)
	{
		printf("\nAre you sure you have exported your saves using fbi and put them in a folder named mk7se on the root of your sd card?\n\nFor steps open:- https://github.com/Pirater12/Mk7se/blob/master/README.md\n\nMk7se will soon support direct save import and export\n\nPress start to exit");
        return 1;
		}
    fp2 = fopen(az, "wb+");
  
    fseek(fp1, 0, SEEK_END); // file pointer at end of file

    pos = ftell(fp1);

    fseek(fp1, 0, SEEK_SET); // file pointer set at start

    while (pos--)

    {

        ch = fgetc(fp1);  // copying file character by character

        fputc(ch, fp2);

    }    

   printf("File copied Successfully!");
   fclose(fp1);
   fclose(fp2);
   return 0;
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
	u64 id=0x0004000000030700;
	u8* buf=malloc(sizeof(u8*));
    u64 bSize = 0;
	FS_Archive saveArch;
	Result ret=1;
	Result res=1;
	char*sys="/mk7se/system0.dat";
	char filez[100];
	char file[100];
	int x=0;
	for(x=0;x<10;x++)
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
        puts("Going to make backup");
		ret=make_b(file,--x);
		if(ret==1)
		{
			while(aptMainLoop())
			{ 
				hidScanInput();
                u32 kDown = hidKeysDown();
				if(kDown & KEY_START)
					break;
			
			}
		gfxExit();
		return 0;
		}
		ret=make_b(filez,++x);
	    
		
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
