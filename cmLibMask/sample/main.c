/*
sample
*/
#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspctrl_kernel.h>

#include <stdio.h>
#include <string.h>

#include "cmLibMask.h"

/*-----------------------------------------------------------------*/

PSP_MODULE_INFO("mask_sample", 0x1000, 0, 0);


/*------------------------------------------------------------------*/

// プロトタイプ宣言
int main_thread(SceSize args, void *argp);
int module_start(SceSize args, void *argp);
int module_stop(SceSize args, void *argp);

/*------------------------------------------------------------------*/


bool status = false;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  INIT METHOD		by SnyFbSx and estuibal
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
char cmLibMask_path[] = { "ms0:/seplugins/lib/cmLibMask.prx"};
//------------------------------------------------------
int LoadStartModule(char *module)
{
	SceUID mod = sceKernelLoadModule(module, 0, NULL);

	if (mod < 0)
		return mod;

	return sceKernelStartModule(mod, strlen(module)+1, module, NULL, NULL);
}

int load_module( char *prx_title, char *prx_path )
{
	if( sceKernelFindModuleByName( prx_title ) == NULL ) {
		LoadStartModule( prx_path );
		if( sceKernelFindModuleByName( prx_title ) == NULL ) {
			prx_path[0] = 'e';
			prx_path[1] = 'f';
			LoadStartModule( prx_path );
		}
	}
	sceKernelDelayThread( 1000 );
	return 0;
}


int init(void)
{
	while(1)
	{
		if(sceKernelFindModuleByName("sceKernelLibrary")){
			// prxlibmenu loading Check
			load_module("cmLibMask",cmLibMask_path);

			break;
		}
		
		sceKernelDelayThread(1000);
	}
	return 0;
}

//メイン
int main_thread(SceSize args, void *argp)
{

	init();

	SceCtrlData pad;
	
	while (1)
	{
		
		sceKernelDelayThread(50000);
		sceCtrlPeekBufferPositive(&pad, 1);
		
		if((pad.Buttons & PSP_CTRL_HOME)&&(pad.Buttons & PSP_CTRL_TRIANGLE))
		{	
			maskAllButtonOn(&status);
			//アドレスを渡さないとおかしくなる
		}
		else if((pad.Buttons & PSP_CTRL_HOME)&&(pad.Buttons & PSP_CTRL_CIRCLE))
		{
			maskAllButtonOff(&status);
			//アドレスを渡さないとおかしくなる
		}
		else if((pad.Buttons & PSP_CTRL_HOME)&&(pad.Buttons & PSP_CTRL_CROSS))
		{
			maskButtonOn(PSP_CTRL_UP + PSP_CTRL_RIGHT);
		}
		else if((pad.Buttons & PSP_CTRL_HOME)&&(pad.Buttons & PSP_CTRL_SQUARE))
		{
			maskButtonOff(PSP_CTRL_UP + PSP_CTRL_RIGHT);
		}
	}

	return 0;
}


int module_start(SceSize args, void *argp)
{

	int thid = sceKernelCreateThread("mask_sample", main_thread, 32, 0x800, 0, NULL);
	if(thid >= 0)sceKernelStartThread(thid, args, argp);

	return 0;
}


int module_stop(SceSize args, void *argp)
{
	return 0;
}
