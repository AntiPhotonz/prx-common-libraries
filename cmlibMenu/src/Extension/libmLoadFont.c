#include "common.h"
#include "memory.h"

extern const char *font_cg, *font_hankaku_kana, *font_sjis;
extern const char *font_icon;

//static int loaded_cg = 0, loaded_hankaku_kana = 0, loaded_sjis = 0, loaded_icon = 0;

int libmLoadFont(int flag){
    SceUID fd;
    SceSize size, readsize;
    char *font_buf;
    char path[64] = "ms0:/seplugins/lib/font/";
    char *font_bin[] = {"cg.bin", "hankaku_kana.bin", "sjis.bin", "icon.bin"};
    int k1;
    //int *loaded[4] = {&loaded_cg, &loaded_hankaku_kana, &loaded_sjis, &loaded_icon};
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
    font_buf = psp_malloc(1, size);
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
        psp_free(font_buf);
        pspSdkSetK1(k1);
        return -4;
    }
    
    *font_addr[flag - 1] = (u32)font_buf;
    //*loaded[flag - 1] = 1;
    /*
    switch(flag){
        case LIBM_FONT_CG:
            font_cg = font_buf;
            loaded_cg = 1;
            break;
        
        case LIBM_FONT_HANKAKU_KANA:
            font_hankaku_kana = font_buf;
            loaded_hankaku_kana = 1;
            break;
        
        case LIBM_FONT_SJIS:
            font_sjis = font_buf;
            loaded_sjis = 1;
            break;
        
        case LIBM_FONT_ICON:
            font_icon = font_buf;
            loaded_icon = 1;
            break;
    }
    */
    pspSdkSetK1(k1);
    
    return 0;
}

