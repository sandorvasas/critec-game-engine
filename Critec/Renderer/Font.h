
#ifndef __CRITEC_FONT_H__
#define __CRITEC_FONT_H__

#include <windows.h>
#pragma hdrstop

typedef struct crFontStyle_s {
	HDC			hDC;
	float		fColor[4];
	bool		bBold;
	bool		bUnderline;
	bool		bStrikeOut;
	bool		bItalic;
	int			iSize;
	char*		Fontname;
} crFontStyle_t;


class crFont {
public:
					crFont( void ) {};
	explicit		crFont( crFontStyle_t fontStyle );
					~crFont( void );

	void			InstallFont( char* fontfilename );
	void			RemoveFont( char* fontfilename );
	void			Create( crFontStyle_t fontStyle );
	void			Write( float x, float y, char* text, ... );

protected:
	crFontStyle_t	Style;
	unsigned int	list;
};

#endif