#include "common.h"

inline void libmCircle( int x, int y, u32 radius, u32 color )
{
	int cx = 0, cy = radius;
	int d = 3 - 2 * radius;
	
	if( color == LIBM_NO_DRAW || ! radius ) return;
	
	/* �J�n�_ */
	libmPoint( libmMakeDrawAddr(x, y + radius), color ); /* ( 0, R) */
	libmPoint( libmMakeDrawAddr(x, y - radius), color ); /* ( 0,-R) */
	libmPoint( libmMakeDrawAddr(x + radius, y), color ); /* ( R, 0) */
	libmPoint( libmMakeDrawAddr(x - radius, y), color ); /* (-R, 0) */
	
	for( cx = 0; cx <= cy; cx++ )
	{
		if( d >= 0 )
		{
			d += 10 + 4 * cx - 4 * cy--;
		}
		else
		{
			d += 6 + 4 * cx;
		}
		
		libmPoint( libmMakeDrawAddr(x + cy, y + cx), color ); /*   0-45  �x */
		libmPoint( libmMakeDrawAddr(x + cx, y + cy), color ); /*  45-90  �x */
		libmPoint( libmMakeDrawAddr(x - cx, y + cy), color ); /*  90-135 �x */
		libmPoint( libmMakeDrawAddr(x - cy, y + cx), color ); /* 135-180 �x */
		libmPoint( libmMakeDrawAddr(x - cy, y - cx), color ); /* 180-225 �x */
		libmPoint( libmMakeDrawAddr(x - cx, y - cy), color ); /* 225-270 �x */
		libmPoint( libmMakeDrawAddr(x + cx, y - cy), color ); /* 270-315 �x */
		libmPoint( libmMakeDrawAddr(x + cy, y - cx), color ); /* 315-360 �x */
	}
}
