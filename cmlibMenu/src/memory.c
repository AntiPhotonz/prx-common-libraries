// memory.c
// Author: wn

#include <pspkernel.h>

void *psp_malloc(int partition, SceSize size){
    SceUID memid;
    void *ret;
    
    memid = sceKernelAllocPartitionMemory(partition, "cmlibMenuFont", 1, size + sizeof(SceUID), NULL);
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

