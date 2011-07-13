#include "common.h"
#include "memory.h"

extern const char *font_cg, *font_hankaku_kana, *font_sjis;
extern const char *font_icon;

static int loaded_cg = 0, loaded_hankaku_kana = 0, loaded_sjis = 0, loaded_icon = 0;

int libmLoadFont(int flag){
    SceUID fd;
    SceSize size, readsize;
    char *font_buf;

    switch(flag){
        case LIBM_FONT_CG:
            if(loaded_cg){
                return 0;
            }
            else{
                // file open
                fd = sceIoOpen("ms0:/seplugins/lib/font/cg.bin", PSP_O_RDONLY, 0777);
                if(fd < 0){
                    fd = sceIoOpen("ef0:/seplugins/lib/font/cg.bin", PSP_O_RDONLY, 0777);
                    if(fd < 0){
                        return -1;
                    }
                }
            }
            break;
        
        case LIBM_FONT_HANKAKU_KANA:
            if(loaded_hankaku_kana){
                return 0;
            }
            else{
                // file open
                fd = sceIoOpen("ms0:/seplugins/lib/font/hankaku_kana.bin", PSP_O_RDONLY, 0777);
                if(fd < 0){
                    fd = sceIoOpen("ef0:/seplugins/lib/font/hankaku_kana.bin", PSP_O_RDONLY, 0777);
                    if(fd < 0){
                        return -1;
                    }
                }
            }
            break;
        
        case LIBM_FONT_SJIS:
            if(loaded_sjis){
                return 0;
            }
            else{
                // file open
                fd = sceIoOpen("ms0:/seplugins/lib/font/sjis.bin", PSP_O_RDONLY, 0777);
                if(fd < 0){
                    fd = sceIoOpen("ef0:/seplugins/lib/font/sjis.bin", PSP_O_RDONLY, 0777);
                    if(fd < 0){
                        return -1;
                    }
                }
            }
            break;
        
        case LIBM_FONT_ICON:
            if(loaded_icon){
                return 0;
            }
            else{
                // file open
                fd = sceIoOpen("ms0:/seplugins/lib/font/icon.bin", PSP_O_RDONLY, 0777);
                if(fd < 0){
                    fd = sceIoOpen("ef0:/seplugins/lib/font/icon.bin", PSP_O_RDONLY, 0777);
                    if(fd < 0){
                        return -1;
                    }
                }
            }
            break;
        
        default:
            return -1;
    }
    
    // get file size
    size = sceIoLseek(fd, 0, SEEK_END);
    if(size <= 0){
        sceIoClose(fd);
        return -1;
    }
    
    // malloc
    font_buf = psp_malloc(1, size);
    if(font_buf == NULL){
        sceIoClose(fd);
        return -1;
    }
    
    // read font
    sceIoLseek(fd, 0, SEEK_SET);
    readsize = sceIoRead(fd, font_buf, size);
    sceIoClose(fd);
    if(readsize != size){
        return -1;
    }
    
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
    
    return 0;
}

