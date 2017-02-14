// Copyright (C) 2007 by Sandor Vasas

#ifndef __CRITEC_TEXTURE_H_
#define __CRITEC_TEXTURE_H_

#include "../../misc/sys.h"
#include "../Managers/FileManager.h"
#include "gl/glexp.h"
//

#ifndef MAKEFOURCC
#define MAKEFOURCC(c0, c1, c2, c3)									\
	(unsigned int)													\
	(																\
		(((unsigned int) (unsigned char)(c3) << 24) & 0xFF000000) |	\
		(((unsigned int) (unsigned char)(c2) << 16) & 0x00FF0000) |	\
		(((unsigned int) (unsigned char)(c1) <<  8) & 0x0000FF00) |	\
		( (unsigned int) (unsigned char)(c0)      ) & 0x000000FF))
#endif

#define FOURCC_DXT1	MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT3	MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT5	MAKEFOURCC('D', 'X', 'T', '5')


	struct TextureData {
		unsigned int	id;
		GLsizei			width;
		GLsizei			height;
		unsigned char*	texels;
		GLenum			format;
		int				internalFormat;
		int				numMipmaps;
	};


	struct DDSURFACEDESC2 {
		DWORD			dwSize;
		DWORD			dwFlags;
		DWORD			dwHeight;
		DWORD			dwWidth;
		DWORD			dwPitchOrLinearSize;
		DWORD			dwDepth;
		DWORD			dwMipMapCount;
		DWORD			dwReserved[11];
	
		struct {
			DWORD	dwSize;
			DWORD	dwFlags;
			DWORD	dwFourCC;
			DWORD	dwRGBBitCount;
			DWORD	dwRBitMask;
			DWORD	dwGBitMask;
			DWORD	dwBBitMask;
			DWORD	dwRGBAlphaBitMask;	
		} ddpfPixelFormat;

		struct  {
			DWORD	dwCaps1;
			DWORD	dwCaps2;
			DWORD	dwReserved[2];
		} ddsCaps;

		DWORD			dwReserved2;
	};

	unsigned int	LoadBMPTexture( char* filename, bool alpha );
	unsigned int	LoadDDSTexture( char* filename );
	unsigned int	CreateEmptyTexture( int, int );

	TextureData*	LoadBMPFile( char *filename );
	TextureData*	LoadDDSFile( char *filename );



#endif