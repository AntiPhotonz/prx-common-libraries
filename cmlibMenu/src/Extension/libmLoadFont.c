#include "common.h"
#include "memory.h"

extern const char *font_cg, *font_hankaku_kana, *font_sjis;
extern const char *font_icon;

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
    font_buf = mem_alloc(size);
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

