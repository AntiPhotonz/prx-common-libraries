/*
 * debuglog.h
 * 2011/09/25
 * Created by Y.K
 */

#ifndef _DEBUGLOG_H_
#define _DEBUGLOG_H_

#include <pspkernel.h>
#include <stdio.h>
#include <string.h>

#if defined(DEBUG)

#define DBG_LOG_FILE 	"ms0:/cmlibUpdate.log"

static SceUID dbg_fd;
static char dbg_buf[1024];

// mainä÷êîìôàÍî‘ç≈èâÇ…åƒÇ—èoÇ∑
#define DBG_INIT(...) \
	dbg_fd = sceIoOpen( DBG_LOG_FILE, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777 ); \
	sceIoClose( dbg_fd ); \

// ÉçÉOèëÇ´çûÇ›ä÷êî printfä÷êîÇ∆ìØÇ∂àµÇ¢Ç≈OKÇ≈Ç∑
#define DBG_LOG(...) \
	dbg_fd = sceIoOpen( DBG_LOG_FILE, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_APPEND, 0777 ); \
	sprintf( dbg_buf, "FILE:%s, \tLINE:%03d  \t", __FILE__, __LINE__ ); \
	sprintf( dbg_buf + strlen(dbg_buf), __VA_ARGS__ ); \
	strcat( dbg_buf, "\r\n" ); \
	sceIoWrite( dbg_fd, dbg_buf, strlen(dbg_buf) ); \
	sceIoClose( dbg_fd ); \

#else
#define DBG_INIT(...)
#define DBG_LOG(...)
#endif

#endif // _DEBUGLOG_H_
