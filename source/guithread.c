#include "libs.h"

void guithread(void * arg)
{	
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x00,0xB5, 0xB5, 0xFF));
	sf2d_set_vblank_wait(0);
	sftd_init();
	gui.font = sftd_load_font_mem(font_ttf, font_ttf_size);
	while(runThread)
	{	
		svcWaitSynchronization(event, U64_MAX);
      //svcClearEvent(event);
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		gui.topFunc();
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		gui.botFunc();
		sf2d_swapbuffers();
	}
	sftd_free_font(gui.font);
	sftd_fini();
	sf2d_fini();
	threadExit(0);
}