#include "framebuffer.h"

void crFrameBuffer2D::Generate( int width, int height, int samples ) {
	/*
	====================================================================================================
	 BEFEJEZNI
	    http://www.gamedev.ru/community/opengl/articles/framebuffer_object?page=4
	====================================================================================================
	*/

/*	unsigned int multisampleFramebuffer, Framebuffer;
	unsigned int color, depth[2];

	glGenRenderbuffersEXT(1, &color);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, color);
	glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, samples, GL_RGBA8, width, height);

	glGenRenderbuffersEXT(1, &depth[0]);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth[0]);
	glRenderBufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, samples, GL_DEPTH_COMPONENT24, width, height);

	glGenFramebuffersEXT(1, &multisampleFramebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, multisampleFramebuffer);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, color[0]);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth[0]);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	/*
	====================================================================================================
	 IDÁIG
	====================================================================================================
	*/

	glGenTextures(1, &texture);
	glGenRenderbuffersEXT(1, &rbuffer);
	glGenFramebuffersEXT(1, &fbuffer);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbuffer);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture, 0);

	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rbuffer);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, NULL);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, NULL);

	this->width = width;
	this->height = height;

}

void crFrameBuffer2D::Bind( void ) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbuffer);
}

void crFrameBuffer2D::Unbind( void ) {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

