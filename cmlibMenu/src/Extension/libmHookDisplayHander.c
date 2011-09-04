#include <systemctrl.h>
#include "common.h"

//from libhook_test_2 by hiroi01
/*------------------------------------------------------------*/

int (*sceDisplaySetFrameBuf_Real)(void *topaddr, int bufferwidth, int pixelformat, int sync);
int (*sceDisplaySetFrameBuf_Hander)(void *topaddr, int bufferwidth, int pixelformat, int sync) = NULL;

/*------------------------------------------------------------*/

int sceDisplaySetFrameBuf_Patched(void *topaddr, int bufferwidth, int pixelformat, int sync)
{
	if( sceDisplaySetFrameBuf_Hander ){
		sceDisplaySetFrameBuf_Hander(topaddr, bufferwidth, pixelformat, sync);
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
void* libmHookDisplayHander(int (*func)(void *topaddr, int bufferwidth, int pixelformat, int sync))
{
	if(sceDisplaySetFrameBuf_Hander == NULL)
	{
		init();
	}

	void *previous = sceDisplaySetFrameBuf_Hander;
	sceDisplaySetFrameBuf_Hander = func;
	return previous;
}

