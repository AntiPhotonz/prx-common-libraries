// cmlibCtrlHook2 by plum

// header
#include "cmlibctrlhook.h"
#include <systemctrl.h>
#include <string.h>

// info
PSP_MODULE_INFO("cmlibCtrlHook", PSP_MODULE_KERNEL, 2, 0);
PSP_NO_CREATE_MAIN_THREAD();

// define
#define K_EXTRACT_CALL(x) (((((u32)_lw((u32)x)) & ~0x0C000000) << 2) | 0x80000000)
#define MAKE_STUB(a, f) _sw(0x08000000 | (((u32)(f) & 0x0FFFFFFC) >> 2), a); _sw(0, a + 4);

// struct
typedef struct InvalidButtonsList
{
	struct InvalidButtonsList *next;
	struct InvalidButtonsList *prev;
	int id;
	u32 buttons;
} InvalidButtonsList;

// prototype
int sceCtrlCommonFunc(SceCtrlData *pad_data, int count, int arg2, int func_number);
void sceCtrlCommonFuncPatched(SceCtrlData *pad_data, int count, int arg2, int func_number);

// global
int list_count;
u32 ctrl_version;
u32 ctrl_jump_addr;
CTRL_HOOK_HANDLER global_handler;
InvalidButtonsList *top;

// function
void ClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

void *malloc_p(SceSize size)
{
	void *ptr;
	SceUID memid;

	memid = sceKernelAllocPartitionMemory(2, "libCtrlHook", PSP_SMEM_High, size + 4, NULL);

	if(memid < 0)
		return NULL;

	ptr = sceKernelGetBlockHeadAddr(memid);

	memcpy(ptr, &memid, 4);
	return ptr + 4;
}

void free_p(void *ptr)
{
	SceUID memid;

	if(ptr != NULL)
	{
		memcpy(&memid, ptr - 4, 4);
		sceKernelFreePartitionMemory(memid);
	}

	return;
}

int libCtrlHookGetRawData(SceCtrlData *pad_data)
{
	return sceCtrlCommonFunc(pad_data, 1, 0, 0);
}

CTRL_HOOK_HANDLER libCtrlHookSetHandler(CTRL_HOOK_HANDLER new_handler)
{
	CTRL_HOOK_HANDLER handler;

	handler = global_handler;
	global_handler = (void *)(((u32)new_handler) | 0x80000000);

	return handler;
}

int libCtrlHookSetInvalidButtons(u32 invalid_buttons)
{
	InvalidButtonsList *new_list, *list;

	// create
	new_list = malloc_p(sizeof(InvalidButtonsList));

	// count
	list_count += 1;

	// set value
	new_list->next = NULL;
	new_list->id = list_count;
	new_list->buttons = invalid_buttons;

	// set pointer
	if(!top)
	{
		top = new_list;
	}
	else
	{
		// set
		list = top;

		// search
		while(list->next != NULL)
			list = list->next;

		// set pointer
		new_list->prev = list;
		list->next = new_list;
	}

	return list_count;
}

void libCtrlHookDeleteInvalidButtons(int id)
{
	InvalidButtonsList *list, *prev;

	if(list_count == 0)
		return;

	// set
	list = top;

	// search id
	while(list != NULL)
	{
		// match
		if(list->id == id)
		{
			// set pointer
			prev = list->prev;
			prev->next = list->next;

			// free
			free_p(list);
			list_count -= 1;

			break;
		}

		// next
		list = list->next;
	}

	return;
}

int sceCtrlCommonFuncControl(SceCtrlData *pad_data, int result)
{
	InvalidButtonsList *list = top;

	if(global_handler)
	{
		global_handler(pad_data);
	}

	if(list_count)
	{
		while(list != NULL)
		{
			// invalid
			pad_data->Buttons &= ~(list->buttons);

			// next
			list = list->next;
		}
	}

	return result;
}

void HookControllerService(void)
{
	u32 orgaddr, func_addr;

	// sceCtrlReadBufferPositive
	orgaddr = sctrlHENFindFunction("sceController_Service", "sceCtrl", 0x1F803938);

	// check version
	if(ctrl_version)
	{
		// get sceCtrlCommonFunc_addr(6.XX)
		func_addr = K_EXTRACT_CALL(orgaddr + 0xC);
	}
	else
	{
		// get sceCtrlCommonFunc_addr(old)
		func_addr = K_EXTRACT_CALL(orgaddr + 0x8);
	}

	// patch sceCtrlCommonFunc
	if(_lw(func_addr + 0xC) != 0)
	{
		// get sceCtrlCommonFunc_jump_addr
		ctrl_jump_addr = func_addr + 0x10;

		// patch
		MAKE_STUB(ctrl_jump_addr - 0x8, sceCtrlCommonFuncPatched);

		// clear
		ClearCaches();
	}

	return;
}

int module_start(SceSize args, void *argp)
{
	// get version
	int devkit = sceKernelDevkitVersion();

	// get ctrl_version
	if(devkit > 0x06000000)
	{
		ctrl_version = 1;
	}
	else
	{
		ctrl_version = 0;
	}

	// init
	list_count = 0;
	top = NULL;

	// patch
	HookControllerService();
	return 0;
}

int module_stop(SceSize args, void *argp)
{
	return 0;
}

