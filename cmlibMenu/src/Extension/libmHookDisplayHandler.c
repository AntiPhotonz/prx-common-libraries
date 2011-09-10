#include <systemctrl.h>
#include "common.h"

//from libhook_test_2 by hiroi01
/*------------------------------------------------------------*/

int (*sceDisplaySetFrameBuf_Real)(void *topaddr, int bufferwidth, int pixelformat, int sync);
int (*sceDisplaySetFrameBuf_Handler)(void *topaddr, int bufferwidth, int pixelformat, int sync) = NULL;

/*------------------------------------------------------------*/

int sceDisplaySetFrameBuf_Patched(void *topaddr, int bufferwidth, int pixelformat, int sync)
{
	if( sceDisplaySetFrameBuf_Handler ){
		sceDisplaySetFrameBuf_Handler(topaddr, bufferwidth, pixelformat, sync);
	}
	return sceDisplaySetFrameBuf_Real(topaddr, bufferwidth, pixelformat, sync);
}

void ClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

void init()
{
	sceDisplaySetFrameBuf_Real = (void *)FindProc("sceDisplay_Service", "sceDisplay", 0x289D82FE);
	sctrlHENPatchSyscall((u32)sceDisplaySetFrameBuf_Real, sceDisplaySetFrameBuf_Patched);
	ClearCaches();
}
void* libmHookDisplayHandler(int (*func)(void *topaddr, int bufferwidth, int pixelformat, int sync))
{
	if(sceDisplaySetFrameBuf_Handler == NULL)
	{
		init();
	}

	void *previous = sceDisplaySetFrameBuf_Handler;
	sceDisplaySetFrameBuf_Handler = func;
	return previous;
}

