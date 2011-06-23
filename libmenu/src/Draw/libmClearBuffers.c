#include "common.h"

void libmClearBuffers(libm_draw_info *dinfo)
{
	memset(dinfo->vinfo->buffer ,0, dinfo->vinfo->frameSize );
}
