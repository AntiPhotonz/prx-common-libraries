#include "common.h"

//VRAM��Color��`��i�R�s�[�j����ہA
//memcpy���g���Ə������x���Ȃ�

inline void libmPoint(void *adr, u32 src)
{
	u32 tmp = src;
	
	if( convert ) src = convert(src);
	
	if( blend )
	{
		src = blend((vinfo.format == PSP_DISPLAY_PIXEL_FORMAT_4444 ? tmp >> 8 : tmp >> 24 ),src,(vinfo.format == PSP_DISPLAY_PIXEL_FORMAT_8888 ? *(u32*)adr : *(u16*)adr));
	}
	
	if( vinfo.format == PSP_DISPLAY_PIXEL_FORMAT_8888 )
	{
		*(u32*)adr = src;
	}
	else
	{
		*(u16*)adr = src;
	}
	
	//memcpy(adr,&src,vinfo.pixelSize);
}