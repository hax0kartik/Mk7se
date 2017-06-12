#include "libs.h"
char message[40];
Result ret = 1;
char *menu2[] = {"Europe","America","Japan"};
char *opt_menu[]= {"Edit no of coins","Edit no of wins","Edit no of lose","Edit VR","Unlock all tracks","Unlock all characters",
	"Unlock all Karts","Unlock all tires","Unlock all gliders"};
/////////////////////////////////////////////////////
void botreg(void){
	sftd_draw_textf(gui.font, 10, 10, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", "Please select your game's \nregion...");
}
void botreg2(void){
	sftd_draw_textf(gui.font, 10, 10, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", "Please select an option...");
	sftd_draw_textf(gui.font, 10, 40, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", "Press start to save and Exit.");
	sftd_draw_textf(gui.font, 10, 70, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", "Press select to Exit without saving.");
	
}
void topreg(void){
	for(int i=0; i!=gui.menu.options; i++){
		if(i == gui.menu.selected)
		{
			if(gui.menu.options == 3)
				{
					sftd_draw_textf(gui.font,(400-(strlen(menu2[i])*11))/2, 25*i, RGBA8(0xf2,0x32,0x32,0xf0), 20, "%s",menu2[i]);
					sf2d_draw_rectangle(0, 25*i-1, 400, 25, RGBA8(0xff,0x12,0x56,0x6f));
				}	
			else
				{
					sftd_draw_textf(gui.font,(400-(strlen(opt_menu[i])*11))/2, 25*i, RGBA8(0xf2,0x32,0x32,0xf0), 20, "%s",opt_menu[i]);
					sf2d_draw_rectangle(0, 25*i-1, 400, 25, RGBA8(0xff,0x5f,0xdf,0x6f));
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
	sftd_draw_textf(gui.font, 10,120, RGBA8(0xf9,0xf9,0xf9,255), 15, "%s","Please wait while your saves are being imported...");
}
void botWait(void)
{
	sftd_draw_textf(gui.font, 10,105, RGBA8(0xf9,0xf9,0xf9,255), 30, "%s","...");
}
u64 titleid = 0x0000000000000000;
//////////////////////////////////////////////////
void topFail(void)
{
	sftd_draw_textf(gui.font,10,105, RGBA8(0xf9,0xf9,0xf9,255),15,"%08X|%llX|%d",ret,titleid,gui.menu.selected);
}
void botFail(void)
{
	sftd_draw_textf(gui.font,(320-(3*17))/2,112, RGBA8(0xf4,0x46,0x47,250),15,"%s","Press Start to Exit");
	
}
////////////////////////////////////////////////////
int a;
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
	for(a = 0; a<=8; a++){	
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
}
////////////////////////////////////////////////////////
char mybuf[100];

static SwkbdCallbackResult MyCallback(void* user, const char** ppMessage, const char* text, size_t textlen)
{
	if (strcmp(text, "0")== 0)
	{
		*ppMessage = "Entering 0 doesn't work right now, enter some other number.";
		return SWKBD_CALLBACK_CONTINUE;
	}

	return SWKBD_CALLBACK_OK;
}

unsigned int openSwkdb(SwkbdState *swkbd,char *texgen)
{
	SwkbdButton button = SWKBD_BUTTON_NONE;
	//gui.topFunc = topFail;
	
	swkbdInit(swkbd, SWKBD_TYPE_NUMPAD, 2, -1);
	//gui.topFunc = topFail;
	swkbdSetFilterCallback(swkbd, MyCallback, NULL);
	button = swkbdInputText(swkbd, mybuf, sizeof(mybuf));
	int w=atoi(mybuf);
	return w;
}
void botDisplay(void)
{
	sftd_draw_textf(gui.font,(320-(strlen(message)*11))/2, 110, RGBA8(0xf9,0xf9,0xf9,255), 20, "%s", message);
}
//////////////////////////////////////////////////////////
void HandleHIDOptions(int selected)
{
	unsigned int opt = 0;
	SwkbdState swkbd;
	u8 * non = malloc(sizeof(u8*)*2);
	memset(non, '\0', 4);
	switch(selected)
	{
		case 0:
		svcCreateEvent(&event,RESET_STICKY);
		opt = openSwkdb(&swkbd,"Enter no of coins");
		svcSignalEvent(event);
		//svcClearEvent(event);
		patchByte(data,opt,COIN);
		patchByte(data2,opt,COIN);
		strcpy(message, "Number of coins changed!");
		gui.botFunc = botDisplay;
		break;
		case 1:
		svcCreateEvent(&event,RESET_STICKY);
		opt = openSwkdb(&swkbd,"Enter no of wins");
		svcSignalEvent(event);
		splitByte(non,(unsigned long)opt);
		for(int i = 0; non[i] != '\0'; i++)
		{
			data[WIN + i] = non[i];
			data2[WIN + i] = non[i];
		}
		strcpy(message, "Number of wins changed!");
		gui.botFunc = botDisplay;
		break;
		
		case 2:
		svcCreateEvent(&event,RESET_STICKY);
		opt = openSwkdb(&swkbd,"Enter no of Losses");
		svcSignalEvent(event);
		splitByte(non,(unsigned long)opt);
		for(int i = 0; non[i] != '\0'; i++)
		{
			data[LOSE + i] = non[i];
			data2[LOSE + i] = non[i];
		}
		strcpy(message, "Number of losses changed!");
		gui.botFunc = botDisplay;
		break;
		
		case 3:
		svcCreateEvent(&event,RESET_STICKY);
		opt = openSwkdb(&swkbd,"Enter the new VR");
		svcSignalEvent(event);
		patchByte(data, opt, VR);
		patchByte(data2, opt, VR);
		strcpy(message, "VR changed!");
		gui.botFunc = botDisplay;
		break;
		
		case 4:
		patchByte(data, 63, TRACK);
		patchByte(data2, 63, TRACK);
		strcpy(message, "All tracks unlocked!");
		gui.botFunc = botDisplay;
		break;
		
		case 5:
		patchByte(data, 255, CHAR);
		patchByte(data, 1, CHAR+1);
		patchByte(data, 255, CHAR+2);
		patchByte(data, 1, CHAR+3);
		patchByte(data2, 255, CHAR);
		patchByte(data2, 1, CHAR+1);
		patchByte(data2, 255, CHAR+2);
		patchByte(data2, 1, CHAR+3);
		strcpy(message, "All characters unlocked");
		gui.botFunc = botDisplay;
		break;
		
		case 6:
		patchByte(data, 255, KART);
		patchByte(data, 63, KART+1);
		patchByte(data2, 255, KART);
		patchByte(data2, 63, KART+1);
		strcpy(message, "All karts unlocked!");
		gui.botFunc = botDisplay;
		break;
		
		case 7:
		patchByte(data, 127, TIRE);
		patchByte(data2, 127, TIRE);
		strcpy(message, "All tires unlocked!");
		gui.botFunc = botDisplay;
		break;
		
		case 8:
		patchByte(data, 63, GLIDER);
		patchByte(data2, 63, GLIDER);
		strcpy(message, "All gliders unlocked!");
		gui.botFunc = botDisplay;
		break;
	}
	cal_save(data);
	cal_save(data2);
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
	thread = threadCreate(guithread,NULL,(8*1024),0x24,-2,true);
	while (aptMainLoop()) {
		gspWaitForVBlank();
		hidScanInput();
		if (hidKeysDown() & KEY_START){
			if(ret == 0)
			{
				ret = save_export(data, titleid, file);
				sprintf(file,"/system%d.dat",a);
				save_export(data2, titleid, file);
			}
			break;
		}
		if (hidKeysDown() & KEY_SELECT){
			break;
		}
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
			if(gui.menu.options == 3)
				HandleHIDRegion(gui.menu.selected);
			else
				HandleHIDOptions(gui.menu.selected);
		}	
		
	}
	runThread = false;
	fsExit();
	threadJoin(thread, U64_MAX);
	if(event!=NULL)
	svcClearEvent(event);
	free(data);
	free(data2);
	free(file);
	return 0;
}