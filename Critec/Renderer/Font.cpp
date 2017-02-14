#include "Font.h"
#include "GL/GLexp.h"
#include <stdio.h>

crFont::crFont( crFontStyle_t fontStyle ) {
	Create(fontStyle);
}

crFont::~crFont( void ) {
	glDeleteLists(list, 220);
}

void crFont::InstallFont( char* fontfilename ) {
	AddFontResource(fontfilename);
}

void crFont::RemoveFont( char* fontfilename ) {
	RemoveFontResource(fontfilename);
}
void crFont::Create( crFontStyle_t fontStyle ) {
	this->Style = fontStyle;

	list = glGenLists(256);
	HFONT font = CreateFont( Style.iSize, 0, 0, 0,
							(Style.bBold)?FW_BOLD : FW_NORMAL, 
							 Style.bItalic,
							 Style.bUnderline,
							 Style.bStrikeOut,
							 ANSI_CHARSET, 
							 OUT_TT_PRECIS,
							 CLIP_DEFAULT_PRECIS,
							 ANTIALIASED_QUALITY,
							 DEFAULT_PITCH | FF_DONTCARE,
							 Style.Fontname );

	HDC dc = wglGetCurrentDC();
	SelectObject(dc, font);
	//if(!wglUseFontBitmaps(dc, 0, 256, list)) MessageBox(NULL, "Error wglUseFontBitmaps()", "Halting", MB_OK);
	//wglUseFontOutlines(
}

void crFont::Write( float x, float y, char* text, ... ) {
	va_list vlist;
	char text2[2048];

	va_start(vlist, text);
		vsprintf_s(text2, 2048, (const char*)text, vlist);
	va_end(vlist);

	//glMatrixMode(GL_PROJECTION);
	glPushMatrix();

		//glOrtho(0, 800, 600, 0, 0, 1);
	//	glOrtho(-1, 1, -1, 1, -1, 1);
		glLoadIdentity();
		glPushMatrix();
			glColor3f( Style.fColor[0], Style.fColor[1],
				       Style.fColor[2] );

				glRasterPos3f(x, y, -0.1f);

				glPushAttrib(GL_LIST_BIT);
					glListBase(list);
					glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
				glPopAttrib();

			glColor3d( 1, 1, 1 );

		glPopMatrix();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}