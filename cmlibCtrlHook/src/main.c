// ctrl_control_ver0.2		by plum

// header
#include <pspkernel.h>
#include <pspctrl.h>
#include <string.h>
#include "ctrlhook.h"

// define
#define NOP 0x00000000
#define MAKE_JUMP(a, f) _sw(0x08000000 | (((u32)(f) & 0x0FFFFFFC) >> 2), a);

// prototype
int sceCtrlCommonPatched(SceCtrlData *pad, int count, int flag1, int flag2);
void *MainSetHandler(int (*func)(SceCtrlData *pad));
u32 MainSetDeleteButtons(u32 buttons);
void MainGetRawCtrlData(SceCtrlData *pad);

// function_ptr
int (*_sceCtrlCommon)(SceCtrlData *pad, int count, int flag1, int flag2);
void *(*_CtrlControlSetHandler)(int (*func)(SceCtrlData *pad)) = NULL;
u32 (*_SetDeleteButtons)(u32 buttons) = NULL;
void (*_GetRawCtrlData)(SceCtrlData *pad) = NULL;
int (*CtrlController)(SceCtrlData *pad) = NULL;

// global
u32 patch[6];
u32 restore[6];
u32 set_buttons = 0;
SceCtrlData export;
int result = 0;

// function
void libCtrlHookClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

u32 search_sce_ctrl_common_addr(SceModule2 *mod)
{
	u32 text_addr = mod->text_addr;
	u32 text_end = mod->text_addr + mod->text_size;

	for(; text_addr < text_end; text_addr += 4)
	{
		if(_lw(text_addr) == 0x344301FE)
		{
			text_addr -= 0x58;
			break;
		}
	}

	return (text_addr < text_end) ? text_addr : 0;
}

void CtrlControlJumpPatch(void)
{
	MAKE_JUMP(patch[0], sceCtrlCommonPatched);
	_sw(NOP, patch[1]);
	_sw((u32)MainSetHandler, patch[2]);
	_sw((u32)MainSetDeleteButtons, patch[3]);
	_sw((u32)set_buttons, patch[4]);
	_sw((u32)MainGetRawCtrlData, patch[5]);
	libCtrlHookClearCaches();
}

void CtrlControlRestorePatch(void)
{
	set_buttons = (u32)(_lw(patch[4]));
	_sw(restore[0], patch[0]);
	_sw(restore[1], patch[1]);
	_sw(restore[2], patch[2]);
	_sw(restore[3], patch[3]);
	_sw(restore[4], patch[4]);
	_sw(restore[5], patch[5]);
	libCtrlHookClearCaches();
}

void *MainSetHandler(CTRL_HANDLER func)
{
	void *previous = (void *)CtrlController;
	CtrlController = func;
	return previous;
}

void *BackupSetHandler(CTRL_HANDLER func)
{
	return _CtrlControlSetHandler(func);
}

void *libCtrlHookSetHandler(CTRL_HANDLER func)
{
	if(result == 1)
	{
		return MainSetHandler(func);
	}
	else
	{
		return BackupSetHandler(func);
	}
}

u32 MainSetDeleteButtons(u32 buttons)
{
	u32 previous = (u32)(_lw(patch[4]));
	_sw((u32)buttons, patch[4]);
	return previous;
}

u32 BackupSetDeleteButtons(u32 buttons)
{
	return _SetDeleteButtons(buttons);
}

u32 libCtrlHookSetDeleteButtons(u32 buttons)
{
	if(result == 1)
	{
		return MainSetDeleteButtons(buttons);
	}
	else
	{
		return BackupSetDeleteButtons(buttons);
	}
}

void MainGetRawCtrlData(SceCtrlData *pad)
{
	memcpy((void *)pad, (void *)&export, sizeof(SceCtrlData));
}

void BackupGetRawCtrlData(SceCtrlData *pad)
{
	_GetRawCtrlData(pad);
}

void libCtrlHookGetRawCtrlData(SceCtrlData *pad)
{
	if(result == 1)
	{
		MainGetRawCtrlData(pad);
	}
	else
	{
		BackupGetRawCtrlData(pad);
	}
}

int sceCtrlCommonPatched(SceCtrlData *pad, int count, int flag1, int flag2)
{
	int res = 0;
	CtrlControlRestorePatch();

	res = _sceCtrlCommon(pad, count, flag1, flag2);

	memcpy((void *)&export, (void *)pad, sizeof(SceCtrlData));

	if(CtrlController != NULL)
	{
		CtrlController(pad);
	}

	if(set_buttons != 0)
	{
		pad->Buttons &= ~set_buttons;
	}

	CtrlControlJumpPatch();
	return res;
}

int libCtrlHookStartInit(void)
{
	SceModule2 *mod = NULL;
	u32 orgaddr = 0;
	int res = 0;

	mod = sceKernelFindModuleByName("sceController_Service");

	if(mod == NULL)
		return -1;

	orgaddr = search_sce_ctrl_common_addr(mod);

	if(orgaddr == 0)
		return -1;

	if(_lw(orgaddr + 4) != NOP)
	{
		patch[0] = orgaddr;
		patch[1] = orgaddr + 4;
		patch[2] = orgaddr + 8;
		patch[3] = orgaddr + 12;
		patch[4] = orgaddr + 16;
		patch[5] = orgaddr + 20;
		restore[0] = _lw(orgaddr);
		restore[1] = _lw(orgaddr + 4);
		restore[2] = _lw(orgaddr + 8);
		restore[3] = _lw(orgaddr + 12);
		restore[4] = _lw(orgaddr + 16);
		restore[5] = _lw(orgaddr + 20);

		set_buttons = 0;
		memset((void *)&export, 0, sizeof(SceCtrlData));

		_sceCtrlCommon = (void *)orgaddr;
		CtrlControlJumpPatch();
		res = 1;
		result = res;
	}
	else
	{
		_CtrlControlSetHandler = (void *)_lw(orgaddr + 8);
		_SetDeleteButtons = (void *)_lw(orgaddr + 12);
		_GetRawCtrlData = (void *)_lw(orgaddr + 20);
		res = 0;
		result = res;
	}

	return res;
}

