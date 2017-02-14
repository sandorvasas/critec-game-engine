//  Copyright (C) 2007 by Sandor Vasas
//
#ifndef __CRITEC_FRAMEBUFFER_H__
#define __CRITEC_FRAMEBUFFER_H__

#include "gl/GLexp.h"


class crFrameBuffer2D {
public:
	unsigned int	texture;
	unsigned int	fbuffer;
	unsigned int	rbuffer;
	int				width;
	int				height;
public:
	void			Generate( int width, int height, int samples );
	void			Bind( void );
	void			Unbind( void );
};

#endif