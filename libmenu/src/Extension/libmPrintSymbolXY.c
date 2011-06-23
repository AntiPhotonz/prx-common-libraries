#include "common.h"


extern const char *font_cg, *font_hankaku_kana, *font_sjis;

extern const char no_font[];

inline int libmPrintSymbolXY( int x, int y, u32 fg, u32 bg, const char *str )
{
	void *put_addr;
	
	const char *glyph;
	u8  glyph_line_data, chr_width_bytes;
	u16	glyph_x, glyph_y;
	u32	i,color;
	bool flag = false;
	
	int cnt;
	
	if( x == -1 && y == -1 )
	{
		x = psx;
		y = psy;
		flag = true;
	}
	
	for( i = 0,cnt = 0; str[i]; i++,cnt++ )
	{
		if( ( (vinfo.opt & LIBM_DRAW_RETURN) && x > DRAW_CHR_XMAX  ) || (unsigned char)str[i] == '\n' )
		{
			y += LIBM_CHAR_HEIGHT;
			x = 0;
		}
		
		if( (vinfo.opt & LIBM_DRAW_RETURN) && y > DRAW_CHR_YMAX ) y = 0;
		
		//即座に次の文字へ
		if( (unsigned char)str[i] == '\n' || (!(vinfo.opt & LIBM_DRAW_RETURN) && (x > DRAW_CHR_XMAX || y > DRAW_CHR_YMAX)) || x < 0 || y < 0 ) continue;
		
		put_addr = libmMakeDrawAddr( x, y );
		
		/* グリフ取得 */
		
		
		//文字アドレス = 文字コード * 文字高さ（1*8 = 8byte）
		if( (unsigned char)str[i] <= 0x8C )
		{
			glyph = &(font_cg[(unsigned char)str[i] * LIBM_CHAR_HEIGHT]);
		}
		else
		{
			//該当なし => ?
			glyph = no_font;
		}
		
		chr_width_bytes = LIBM_CHAR_WIDTH * vinfo.pixelSize;
		
		for( glyph_y = 0; glyph_y < LIBM_CHAR_HEIGHT; glyph_y++, put_addr += vinfo.lineSize - chr_width_bytes )
		{
			glyph_line_data = glyph[glyph_y];
			
			for( glyph_x = 0; glyph_x < LIBM_CHAR_WIDTH	; glyph_x++, glyph_line_data <<= 1, put_addr += vinfo.pixelSize )
			{
				color = glyph_line_data & 0x80 ? fg : bg;
				
				if( color != LIBM_NO_DRAW ) libmPoint( put_addr, color );
			}
		}
		
		x += LIBM_CHAR_WIDTH;
	}
	
	if( flag )
	{
		psx = x;
		psy = y;
	}
	
	return cnt;
}
