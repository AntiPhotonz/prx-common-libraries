// ctrlhook_sample		by plum

// header
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay_kernel.h>
#include "ctrlhook.h"

// info
PSP_MODULE_INFO("test_ctrl", 0x1000, 0, 1);

// global
CTRL_HANDLER previous;

// function
int test_func(SceCtrlData *pad)
{
	if(pad->Buttons & PSP_CTRL_RTRIGGER)
	{
		pad->Buttons |= PSP_CTRL_RIGHT;
	}

	else if(pad->Buttons & PSP_CTRL_LTRIGGER)
	{
		pad->Buttons |= PSP_CTRL_LEFT;
	}

	return (previous) ? previous(pad) : 0;
}

int main_thread(SceSize args, void *argp)
{
	SceCtrlData pad;
	int level = 30;

	while(1)
	{
		sceKernelDelayThread(50000);
		libCtrlHookGetRawCtrlData(&pad);

		if(pad.Buttons & PSP_CTRL_CIRCLE)
		{
			level++;
			if(level > 99) level = 30;

			sceDisplaySetBrightness(level, 0);
		}
	}

	return 0;
}

int module_start(SceSize args, void *argp)
{
	// patch
	int res = libCtrlHookStartInit();

	if(res == -1)
		return -1;

	// set
	previous = libCtrlHookSetHandler(test_func);
	libCtrlHookSetDeleteButtons(PSP_CTRL_CIRCLE);

	// thread
	SceUID thid = sceKernelCreateThread("ctrl_1", main_thread, 32, 0x800, 0, NULL);
	if(thid >= 0) sceKernelStartThread(thid, args, argp);

	return 0;
}

