// Copyright (C) 2007 by Sandor Vasas
//

/*
===============================================================

	CoreOne source file for the first application 
	created with the Critec Engine.

===============================================================
*/

#include <windows.h>
#include "../Critec/Core.h"

#include "../misc/sys.h"
#include "../game/player.h"
#include "../game/NPC.H"
#include "../game/console.h"

#define WINDOW_TITLE	"Critec Game Engine -!Under Development!-"

class crGameLocal : public crApplication {
public:
	crGameLocal( void ) : crApplication() {};
	~crGameLocal( void );
 
	int						Initialize( const char* wClassName );
	void					Shutdown( void );
	void					HandleMessage( unsigned int, WPARAM, LPARAM );


// Initializing
	void					LoadExtensions( void );
	void					Setup_Textures( void );
	void					Setup_Models( void );
	void					Setup_Game( void );
	void					Setup_Shaders( void );
	void					Setup_OGL_classes( void );
	
// Rendering
	void					RenderWorld( void );
	void					RenderToBuffer( void );
	void					Render( void );
	void					DoPhysics( void );
	void					UpdateApp( void );
	void					ProcessKeys( void );

private:			
	crPlayer				player;				
	crGLSLShader			shaders[8];			
	GLuint					g_tex[20];			
	cr3DSModel				Model, Model2;
	Text					text1;
	crHeightmap				hmap;
	crFrameBuffer2D			screen;
	crSkyDome				Sky;
	crWater*				Water1;
	crFont					font;

	crVec3					lightPos;
};



inline
crGameLocal::~crGameLocal( void ) {
	Shutdown();
}