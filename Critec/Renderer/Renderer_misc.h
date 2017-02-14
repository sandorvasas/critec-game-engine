#ifndef __RENDERER_MISC_H_
#define __RENDERER_MISC_H_

#include <windows.h>
#include "../math/math3D.h"
#include "gl/glexp.h"
#include "texture.h"
#include "OpenGLRenderDevice.h"
#pragma hdrstop


//*******************************
//  struct crTriangle
//*******************************
struct crTriangle {
	int		iVertices[3];
	int		iTexCoords[3];
	int		iNormals[3];
	int		iFNormal;
};



//*******************************
// FONT class [!temporary]
//*******************************
class	Text {
protected:
	HFONT font;
	UINT  id;
//	float color[4];
public:
	Text() {};
	virtual ~Text();

	void	build	(char* fontname, int size);
	void	print	(float x, float y, float* color, char* text,...);
};

//********************************
//  Misc
//********************************

void		ChangeResolution(int width, int height, int bits);

void		glTranslatefv	(const float* FloatPtr);

#endif