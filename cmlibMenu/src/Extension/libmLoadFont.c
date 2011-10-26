#include "common.h"
#include "memory.h"

char *font_cg = NULL, *font_hankaku_kana = NULL, *font_sjis = NULL, *font_icon = NULL;
char no_font[] = {0x7F, 0x63, 0x55, 0x49, 0x49, 0x55, 0x63, 0x7F};

/*---------------------------------------------------------------------------
  メモリ確保 Thanks noname
    int size: 利用メモリサイズ

    return: 確保したメモリへのポインタ
            エラーの場合はNULLを返す
---------------------------------------------------------------------------*/
void* mem_alloc_forLoadFont(int size)
{
  SceUID* p;
  int h_block;

  if(size == 0) return NULL;

  int fw = (sceKernelDevkitVersion() >> 24) - 5;  // 0 = ～5.xx, 1 = 6.xx
  int mode = (sceKernelInitKeyConfig() >> 8) - 1; // 0 = VSH, 1 = GAME, 2 = POPS
  int model = kuKernelGetModel();                 // 0 = 1000, 1 = 2000, 2,3,5,6,7,8 = 3000, 4 = go

  if(mode && model)
  {
    h_block = sceKernelAllocPartitionMemory(8+fw, "mem_alloc", PSP_SMEM_High, size + sizeof(SceUID*), NULL);
    if(h_block <= 0)
      return NULL;

    p = sceKernelGetBlockHeadAddr(h_block);
    *p = h_block;

    return (void *)(p + 1);
  } else {
    return mem_alloc(size);
  }
}


int libmLoadFont(int flag){
    SceUID fd;
    SceSize size, readsize;
    char *font_buf;
    char path[64] = "ms0:/seplugins/lib/font/";
    char *font_bin[] = {"cg.bin", "hankaku_kana.bin", "sjis.bin", "icon.bin"};
    int k1;
    u32 *font_addr[4] = {(u32*)&font_cg, (u32*)&font_hankaku_kana, (u32*)&font_sjis, (u32*)&font_icon};
    
    if(*font_addr[flag - 1]){
        return -1;
    }
    
    k1 = pspSdkSetK1(0);
    
    // make path
    strcat(path, font_bin[flag - 1]);
    
    // file open
    fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if(fd < 0){
        path[0] = 'e';
        path[1] = 'f';
        fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
        if(fd < 0){
            pspSdkSetK1(k1);
            return fd;
        }
    }
    
    // get file size
    size = sceIoLseek(fd, 0, SEEK_END);
    if(size <= 0){
        sceIoClose(fd);
        pspSdkSetK1(k1);
        return -2;
    }
    
    // malloc
    //mem_set_alloc_mode(MEM_AUTO);
    font_buf = mem_alloc_forLoadFont(size);
    if(font_buf == NULL){
        sceIoClose(fd);
        pspSdkSetK1(k1);
        return -3;
    }
    
    // read font
    sceIoLseek(fd, 0, SEEK_SET);
    readsize = sceIoRead(fd, font_buf, size);
    sceIoClose(fd);
    if(readsize != size){
        mem_free(font_buf);
        pspSdkSetK1(k1);
        return -4;
    }
    
    *font_addr[flag - 1] = (u32)font_buf;
    
    pspSdkSetK1(k1);
    
    return 0;
}

