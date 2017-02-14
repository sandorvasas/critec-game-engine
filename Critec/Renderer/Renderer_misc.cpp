#include "Renderer_misc.h"


void	ChangeResolution(int width, int height, int bits) {
	DEVMODE dm;

	EnumDisplaySettings(0, 0, &dm);
	dm.dmSize			= sizeof(DEVMODE);
	dm.dmBitsPerPel		= bits;
	dm.dmPelsWidth		= width;
	dm.dmPelsHeight		= height;
	ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
}

void	Text::build(char* fontname, int size) {
	font = CreateFont(size, 0, 0, 0,
					  FW_DONTCARE, 0, 0, 0,
					  DEFAULT_CHARSET,
					  OUT_TT_PRECIS,
					  CLIP_DEFAULT_PRECIS,
					  ANTIALIASED_QUALITY,
					  DEFAULT_PITCH | FF_DONTCARE,
					  fontname);

	SelectObject(wglGetCurrentDC(), font);
	wglUseFontBitmaps(wglGetCurrentDC(), 32, 220, id);
}

void	Text::print	(	 float x, 	 float y, 	 float *color, 	 char* text,...		) {


	va_list list;
	char	text2[1024];
	va_start(list, text);
		vsprintf_s(text2, sizeof(text2), text, list);
	va_end(list);
	
	renderDevice->SetOrtho();
	
	glPushMatrix();
	glTranslated( 0, 0,  0.1 );

		glColor3f(color[0], color[1], color[2]);

		glRasterPos2f(x, y);
		glPushAttrib(GL_LIST_BIT);
			glListBase(id-32);
			glCallLists(strlen(text2), GL_UNSIGNED_BYTE, text2);
		glPopAttrib();

		glColor3d(1,1,1);

	glPopMatrix();

	renderDevice->SetOrtho(false);
}

Text::~Text () {
	
}

void glTranslatefv (const float* FloatPtr) {
	glTranslatef(FloatPtr[0], FloatPtr[1], FloatPtr[2]);
}

