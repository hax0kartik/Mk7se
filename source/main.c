#include "libs.h"
char *menu2[] = {"Europe","America","Japan"};
char *opt_menu[]= {"Edit no of coins","Edit no of wins","Edit no of lose","Edit VR","Unlock all tracks","Unlock all chars",
	"Unlock all Karts","Unlock all tires","Unlock all gliders"};
/////////////////////////////////////////////////////
void botreg(void){
	sftd_draw_textf(gui.font, 10, 10, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", "Please select your game's region...");
}
void botreg2(void){
	sftd_draw_textf(gui.font, 10, 10, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", "Please select an option...");
}
void topreg(void){
	for(int i=0; i!=gui.menu.options; i++){
		if(i == gui.menu.selected)
		{
			if(gui.menu.options == 3)
				{
					sftd_draw_textf(gui.font,(400-(strlen(menu2[i])*11))/2, 25*i, RGBA8(0xf2,0x32,0x32,0xf0), 20, "%s",menu2[i]);
					sf2d_draw_rectangle(1, 25*i-1, 400, 25, RGBA8(0xff,0x12,0x56,0x6f));
				}	
			else
				{
					sftd_draw_textf(gui.font,(400-(strlen(opt_menu[i])*11))/2, 25*i, RGBA8(0xf2,0x32,0x32,0xf0), 20, "%s",opt_menu[i]);
					sf2d_draw_rectangle(1, 25*i-1, 400, 25, RGBA8(0xff,0x5f,0xdf,0x6f));
				}
		}
		else
		{
			if(gui.menu.options == 3)
				sftd_draw_textf(gui.font,(400-(strlen(menu2[i])*11))/2, 25*i, RGBA8(0xf0,0xf0,0xf0,0xff), 20, "%s",menu2[i]);
			else
				sftd_draw_textf(gui.font,(400-(strlen(opt_menu[i])*11))/2, 25*i, RGBA8(0xf0,0xf0,0xf0,0xff), 20, "%s",opt_menu[i]);
		}		
	}
}
////////////////////////////////////////////////////
void topWait(void)
{
	sftd_draw_textf(gui.font, 10, 105 , RGBA8(0xf9,0xf9,0xf9,255), 15, "%s","Please wait while your saves are being imported...");
}
void botWait(void)
{
	sftd_draw_textf(gui.font, 140, 90 , RGBA8(0xf9,0xf9,0xf9,255), 30, "%s","...");
}
u64 titleid = 0x0000000000000000;
//////////////////////////////////////////////////
void topFail(void)
{
	sftd_draw_textf(gui.font,10,105, RGBA8(0xf9,0xf9,0xf9,255),15,"%08X|%llX|%d",ret,titleid,gui.menu.selected);
}
void botFail(void)
{
	sftd_draw_textf(gui.font,120, 90, RGBA8(0xf4,0x46,0x47,250),15,"%s","Press Start to Exit");
}
////////////////////////////////////////////////////
void HandleHIDRegion(int selected)
{
	switch(selected)
	{
		case 0:
		titleid = 0x0004000000030700;
		break;
		case 1:
		titleid = 0x0004000000030800;
		break;
		case 2:
		titleid = 0x0004000000030600;
		break;
	}
	gui.topFunc = topWait;
	gui.botFunc = botWait;
	file = malloc(0x40);
	for(int a=0; a<=8; a++){	
		sprintf(file, "/system%d.dat", a);
		ret = save_import(data, titleid, file);
		if (ret == 0){
			sprintf(file, "/system%d.dat", a+1);
			ret = save_import(data2, titleid, file);
			break;
		}
	}	
	if(ret!=0)
	{
		gui.topFunc = topFail;
		gui.botFunc = botFail;
	}
	
	else
	{
		gui.menu.selected = 0;
		gui.menu.options = 9;
		gui.topFunc = topreg;
		gui.botFunc = botreg2;
	}
	free(file);
}

//////////////////////////////////////////////////
int main()
{	
	runThread = true;
	gui.menu.selected = 0;
	gui.menu.options = 3;
	gui.topFunc = topreg;
	gui.botFunc = botreg;
	data = malloc(20692);
	data2 = malloc(20692);
	fsInit();
	Thread thread = threadCreate(guithread,NULL,(8*1024),0x24,-2,true);
	while (aptMainLoop()) {
		gspWaitForVBlank();
		hidScanInput();
		if (hidKeysDown() & KEY_START) break;
		if (hidKeysDown() & KEY_DDOWN)
		{
			gui.menu.selected++;
			if(gui.menu.selected == gui.menu.options)
			{
				gui.menu.selected = 0;
			}
		}
		if (hidKeysDown() & KEY_DUP)
		{
			gui.menu.selected--;
			if(gui.menu.selected < 0)
			{
				gui.menu.selected = gui.menu.options - 1;
			}	
		}
		if (hidKeysDown() & KEY_A)
		{
			HandleHIDRegion(gui.menu.selected);
		}	
		
	}
	runThread = false;
	fsExit();
	threadJoin(thread, U64_MAX);
	free(data);
	free(data2);
	return 0;
}
