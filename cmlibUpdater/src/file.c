/*
 * Prx Common Libraries - cmlibUpdater
 * file.c
 * 2011/10/21
 * Created by Y.K
 */

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#include "debuglog.h"


#define MAGIC_PSP 	0x5053507E
#define MAGIC_ELF 	0x464C457F

#define COPY_BUFFER_SIZE 	4096


int get_filetitle( char *dest, const char *path )
{
	char *pos = strrchr( path, '/' );
	if( pos == NULL ) {
		return -1;
	}
	strcpy( dest, ++pos );
	return 0;
}

char *get_curdir( const char *argp )
{
	static char curdir[260];
	if( argp != NULL ) {
		strcpy( curdir, argp );
		char *p = strrchr( curdir, '/' );
		if( p ) *(++p) = '\0';
	}
	return curdir;
}

char *get_device_name( const char *argp )
{
	static char devname[8];
	if( argp != NULL ) {
		strncpy( devname, argp, 5 );
	}
	return devname;
}

char *make_dir( char *dest, const char *devname, const char *path )
{
	if( devname != NULL ) {
		if( !strncmp( path, "ms0:", 4 ) || !strncmp( path, "ef0:", 4 ) ) {
			path += 5;
		}
		if( *path == '/' ) path++;
		strncpy( dest, devname, 5 );
	} else {
		dest[0] = '\0';
	}

	strcat( dest, path );

	char *p;
	for( p = dest; *p != '\0'; p++ ) {
		if( *p == '/' ) {
			*p = '\0';
			sceIoMkdir( dest, 0777 );
			*p = '/'; // restore
		}
	}
	return dest;
}

int get_prx_version( const char *prx, u8 *major, u8 *minor )
{
	SceUID fd = sceIoOpen( prx, PSP_O_RDONLY, 0777 );
	if( fd < 0 ) return -1;

	u32 magic = 0;
	if( sceIoRead( fd, &magic, sizeof magic ) < 0 ) {
		goto error;
	}

	if( magic == MAGIC_PSP ) {
		sceIoLseek( fd, 0x8, SEEK_SET );
	}
	else if( magic == MAGIC_ELF ) {
		u32 offset = 0;
		sceIoLseek( fd, 0x40, SEEK_SET );
		if( sceIoRead( fd, &offset, sizeof offset ) < 0 ) {
			goto error;
		}
		sceIoLseek( fd, (offset & 0x1FFFFFFF) + 2, SEEK_SET );
	} else {
		goto error;
	}

	u16 version = 0;
	if( sceIoRead( fd, &version, sizeof version ) < 0 ) {
		goto error;
	}

	*major = (version >> 8) & 0xFF;
	*minor = version & 0xFF;

	sceIoClose( fd );
	return 0;

error:
	if( fd >= 0 ) sceIoClose( fd );
	return -1;
}

/*
int get_prx_version( u8 *prx_buf, u8 *major_ver, u8 *minor_ver )
{
	if( *(u32 *)prx_buf == MAGIC_PSP ) {
		*major_ver = *(prx_buf + 0x9);
		*minor_ver = *(prx_buf + 0x8);
	}else if( *(u32 *)prx_buf == MAGIC_ELF ) {
		u8 *addr = (u8 *)(*(u32 *)(prx_buf + 0x40) & 0x1FFFFFFF);
		*major_ver = *(addr + 0x3);
		*minor_ver = *(addr + 0x2);
	} else {
		return -1;
	}
	return 0;
} */

int download_file( int sock, const char *file, HTTPResponse *resp, MemArray *mabuf )
{
	SceUID fd = sceIoOpen( file, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777 );
	if( fd < 0 ) {
		DBG_LOG( "Error, failed to create the \"%s\" 0x%08X", file, fd );
		return -1;
	}

	if( resp->content_length > 0 ) {
		sceIoLseek( fd, resp->content_length, SEEK_SET );
		sceIoLseek( fd, 0, SEEK_SET );
	}

	if( sceIoWrite( fd, mabuf->ptr, mabuf->len ) != mabuf->len )
		goto error;

	int nrecv = 0;

	while( 1 ) {
//		memset( mabuf->ptr, 0, mabuf->size );

		if( net_recv_data( sock, mabuf->ptr, mabuf->size, &nrecv ) < 0 )
			goto error;

		if( nrecv == 0 )
			break;

		if( sceIoWrite( fd, mabuf->ptr, nrecv ) != nrecv )
			goto error;
	}

	DBG_LOG( "OK, download_file()" );
	sceIoClose( fd );
	return 0;

error:
	if( fd >= 0 ) sceIoClose( fd );
	DBG_LOG( "Error, download_file()" );
	return -1;
}

/*
int copy_file( const char *dest, const char *src )
{
	SceUID fd_dest = sceIoOpen( dest, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777 );
	if( fd_dest < 0 ) {
		return -1;
	}

	SceUID fd_src = sceIoOpen( src, PSP_O_RDONLY, 0777 );
	if( fd_src < 0 ) {
		sceIoClose( fd_dest );
		return -1;
	}

	SceOff src_size = sceIoLseek( fd_src, 0, SEEK_END );
	sceIoLseek( fd_src, 0, SEEK_SET );
	if( sceIoLseek( fd_dest, src_size, SEEK_SET ) != src_size ) {
		sceIoClose( fd_dest );
		sceIoClose( fd_src );
		return -2;
	}
	sceIoLseek( fd_dest, 0, SEEK_SET );

	char copy_buffer[COPY_BUFFER_SIZE] = "";

	while( 1 ) {
		int nread = sceIoRead( fd_src, copy_buffer, sizeof copy_buffer );
		if( nread <= 0 ) {
			sceIoClose( fd_dest );
			sceIoClose( fd_src );
			return nread;
		}
		if( sceIoWrite( fd_dest, copy_buffer, nread ) != nread ) {
			sceIoClose( fd_dest );
			sceIoClose( fd_src );
			return -3;
		}
	}

	sceIoClose( fd_dest );
	sceIoClose( fd_src );
	return 0;
}
*/


static
int strcpy_CRLF( char *dest, int size, const char *src )
{
	if( size <= 0 ) return 0;
	int len = 0;
	while( *src != '\0' && *src != '\r' && *src != '\n' && len < size ) {
		*dest++ = *src++;
		len++;
	}
	*dest = '\0';
	while( *src != '\0' && *src != '\r' && *src != '\n' ) {
		len++;
	}
	return len;
}

static
int buffering( SceUID *lpfd, char *buf, int bufsize )
{
	SceUID fd = *lpfd;

	int nread = sceIoRead( fd, buf, bufsize - 1 );
	if( nread <= 0 ) {
		sceIoClose( fd ); *lpfd = -1;
		return nread;
	}

	buf[nread] = '\0';
	return 1;
}

int read_line( const char *file, char *dest, int size )
{
	static SceUID fd = -1;
	static char buffer[2048] = "";
	static char *pos = buffer;

	int nret;

	if( file == NULL && fd >= 0 ) {
		sceIoClose( fd );
		fd = -1;
		return 0;
	}

	if( fd < 0 && file == NULL ) {
		return -1;
	}

	if( fd < 0 ) {
		if( (fd = sceIoOpen( file, PSP_O_CREAT | PSP_O_RDONLY, 0777 )) < 0 ) {
			fd = -1;
			return -1;
		}

		if( (nret = buffering( &fd, buffer, sizeof buffer )) <= 0 )
			return nret;

		pos = buffer;
	}

	pos += strcpy_CRLF( dest, size, pos );

	if( *pos == '\r' || *pos == '\n' )
		if( *(++pos) == '\n' ) pos++;

	if( *pos == '\0' ) {
		if( (nret = buffering( &fd, buffer, sizeof buffer )) <= 0 )
			return nret;
		int len = strlen( dest );
		pos = (char *)( buffer + strcpy_CRLF( dest + len, size - len, buffer ) );
	}

	return 1;
}
