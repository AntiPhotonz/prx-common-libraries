// memory.c
// Author: wn

#include <pspkernel.h>

void *psp_malloc(SceSize size){
    SceUID memid;
    void *ret;
    
    memid = sceKernelAllocPartitionMemory(2, "mem", 0, size + sizeof(SceUID), NULL);
    if(memid < 0) return NULL;
    ret = sceKernelGetBlockHeadAddr(memid);
    *(SceUID*)ret = memid;
    ret += sizeof(SceUID);
    
    return ret;
}

void psp_free(void *ptr){
    SceUID memid;
    
    memid = *(SceUID*)(ptr - sizeof(SceUID));
    sceKernelFreePartitionMemory(memid);
}

