#include "common.h"

//����Swap���炵�ĂȂ��E�E�E

void libmSwapBuffers()
{
	sceDisplaySetFrameBuf( vinfo.buffer , vinfo.lineWidth , vinfo.format , PSP_DISPLAY_SETBUF_IMMEDIATE );
	sceDisplayWaitVblankStart();
	sceKernelDelayThread( 11500 );
}
