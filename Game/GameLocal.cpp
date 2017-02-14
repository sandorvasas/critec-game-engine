#include "GameLocal.h"


/*
========================
    RenderWorld
========================
*/
void crGameLocal::RenderWorld( void ) {
		Sky.Render( (float)msElapsedTime/1000.0f );
		hmap.UseShader( true );
		hmap.Render();
	//	Water1->Render( (float)msElapsedTime * 0.001f );
}


/*
========================
    RenderToBuffer
========================
*/
void crGameLocal::RenderToBuffer( void ) {

	RenderWorld();

		glPushMatrix();
			//	glTranslatef(-2.0f, 2.0f, 0.0f);
			//	glRotatef( 90.0f, 1.0, 0.0, 0.0);
			//	glScaled(0.05, 0.05, 0.05);
				Model.ModifyParams( crVec3(100, 500, 100), player.Camera->Position );
				Model.Render();
					renderDevice->DrawPoint(crVec3(100, 500, 100), 1.0f, 0.0f, 0.0f);
		glPopMatrix();
}


/*
========================
    Render
========================
*/
void crGameLocal::Render() {

/*	Water1->BeginRenderReflection(player.Camera,SCREEN_WIDTH, SCREEN_HEIGHT);
		RenderToBuffer();
	Water1->EndRenderReflection();
*/
	screen.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderDevice->LoadIdentity();
		player.UpdateLook();
		RenderToBuffer();
	screen.Unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderDevice->LoadIdentity();

	//renderDevice->DrawSprite( crVec2(-0.97f, -0.8f), crVec2(-0.67f, -0.9f), g_tex[6]);
	renderDevice->SetOrtho(true);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, screen.texture );

			glBegin(GL_QUADS);
			 glMultiTexCoord2f(GL_TEXTURE0, 0.f, 0.f); glVertex3d(-1.0, -1.0, 0.5);
			 glMultiTexCoord2f(GL_TEXTURE0, 1.f, 0.f); glVertex3d( 1.0, -1.0, 0.5);
			 glMultiTexCoord2f(GL_TEXTURE0, 1.f, 1.f); glVertex3d( 1.0,  1.0, 0.5);
			 glMultiTexCoord2f(GL_TEXTURE0, 0.f, 1.f); glVertex3d(-1.0,  1.0, 0.5);
			glEnd();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);	

	renderDevice->SetOrtho(false);

	renderDevice->SwapBuffers();
}

/*
========================
    DoPhysics
========================
*/
void crGameLocal::DoPhysics( void ) {
	player.Camera->ApplyGravity();
	player.Camera->Position.y = hmap.CollidePoint( player.Camera->Position );
//	hmap.lightPos = crVec3(0, 100, 0);//Sky.GetSunPosition();
	hmap.viewPos = player.Camera->Position;
	hmap.lightPos = lightPos;
	//lightPos = player.Camera->Position;
	crCollDetect::Detect_Model3ds_Camera( &Model, player.Camera );
}

/*
========================
    UpdateApp
========================
*/
void crGameLocal::UpdateApp( void ) {
	DefaultUpdateApp();
	DoPhysics();
}

/*
========================
    ProcessKeys
========================
*/
void crGameLocal::ProcessKeys( void ) {
	player.Camera->SetVelocity( 15.0f*frametime );
	if (Keys['W'])    player.Camera->Step( 1, 0, 0);
	if (Keys['S'])    player.Camera->Step(-1, 0, 0);
	if (Keys['A'])    player.Camera->Step(0, -1, 0);
	if (Keys['D'])    player.Camera->Step(0, 1, 0);

	if (Keys[VK_SHIFT])  player.Camera->Run( true );
					else player.Camera->Run(false);
	//if (Keys[VK_SPACE])  player.Camera->Jump();
	if (Keys[VK_CONTROL])player.Camera->Crouch( true );
					else player.Camera->Crouch(false);

	if (Keys['E'])    player.Camera->Step(0.f, 0.0f,  0.5f);
	if (Keys['Q'])    player.Camera->Step(0.f, 0.0f, -0.5f);

	static float lightSpeed = 0.1f;
	if (Keys[VK_UP])	lightPos.z -= lightSpeed;
	if (Keys[VK_DOWN])  lightPos.z += lightSpeed;
	if (Keys[VK_LEFT])  lightPos.x -= lightSpeed;
	if (Keys[VK_RIGHT]) lightPos.x += lightSpeed;
	if (Keys[VK_HOME])  lightPos.y += lightSpeed;
	if (Keys[VK_END])   lightPos.y -= lightSpeed;

	if (Keys[VK_ESCAPE]) Running = false;
}



/*
========================
    Initialize
========================
*/
int crGameLocal::Initialize( const char* wClassName ) {

	GameWindow.x = 0;
	GameWindow.y = 0;
	GameWindow.iWidth = SCREEN_WIDTH;
	GameWindow.iHeight = SCREEN_HEIGHT;
	GameWindow.Title = "Critec";
	GameWindow.ClassName = wClassName;
	CreateGameWindow();

	crInitOptions_t InitOpts;
		InitOpts.bVSync			= true;
		InitOpts.hWindow		= GameWindow.hDesc;
		InitOpts.iAlphaBits		= 0;
		InitOpts.iColorBits		= 32;
		InitOpts.iDepthBits		= 16;
		InitOpts.iStencilBits	= 0;
		InitOpts.iMultiSampling = 0;

	renderDevice = new crOpenGLRenderDevice;
	renderDevice->Initialize( InitOpts );

	LoadExtensions();
	
	/*DestroyGameWindow();
	CreateGameWindow( window_class_name );*/

	ShowWindow(GameWindow.hDesc, SW_SHOW);
	ChangeResolution(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	ShowCursor( false );
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
/*
	InitOpts.iMultiSampling = 0;
	renderDevice->Initialize( InitOpts );
*/
	crProjAttribs_t pAttr;
	pAttr.AspectRatio = 4/3;
	pAttr.farPlane	  = 100000000000000000.0;
	pAttr.nearPlane   = 0.1;
	pAttr.FieldOfView = PI / 180.f * 75.f ;
	renderDevice->SetPerspective( pAttr );

	glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
	
	Setup_Textures();
	Setup_Models();
	Setup_OGL_classes();
	Setup_Game();
	Setup_Shaders();
	
	return 0;
}

void crGameLocal::LoadExtensions( void ) {
	if(!LoadEXT_WGL_EXT_swap_control())				MSGBOX(" Your video card does not support WGL_EXT_swap_control ");
	if(!LoadEXT_WGL_ARB_pixel_format())				MSGBOX(" Your video card does not support WGL_ARB_pixel_format ");
	if(!LoadEXT_GL_EXT_framebuffer_object())		MSGBOX(" Your video card does not support GL_EXT_framebuffer_object ");
	if(!LoadEXT_GL_EXT_framebuffer_blit())			MSGBOX(" Your video card does not support GL_EXT_frambuffer_blit ");
	if(!LoadEXT_GL_EXT_blend_minmax())				MSGBOX(" Your video card does not support GL_EXT_blend_minmax ");
	if(!LoadEXT_GL_EXT_framebuffer_multisample())	MSGBOX(" Your video card does not support GL_EXT_frambuffer_multisample ");
	if(!LoadEXT_GL_ARB_vertex_shader())				MSGBOX(" Your video card does not support GL_ARB_vertex_shader ");
}

/*
========================
    Setup_Textures
========================
*/
void crGameLocal::Setup_Textures() {
	g_tex[0] = LoadDDSTexture("Data\\textures\\land\\snow.dds");
	g_tex[6] = LoadDDSTexture("Data\\textures\\hud\\ak104.dds");
	/*g_tex[1] = LoadDDSTexture("Data\\textures\\wall01_normal.dds");
	g_tex[2] = LoadDDSTexture("Data\\textures\\sky\\skyclouds01.dds");
	g_tex[3] = LoadDDSTexture("Data\\textures\\sky\\sky2.dds");*/
	screen.Generate(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

/*
========================
    Setup_Models
========================
*/
void crGameLocal::Setup_Models() {
	crVec2 t1s = crVec2( 0.1f, 0.1f );
	/*LS.LoadFromFile("Data/maps/hm.bmp", crVec2(0.2f, 0.2f),  
					"Data/textures/buildings/casino/grass.dds", NULL, 
					NULL, NULL,
					NULL, NULL );*/
	crSkyParams_t SP;
	SP.fDampFactor = 0.5f;
	SP.fDaytime    = 5.0f;
	SP.fRadius	   = 5000.0f;
	SP.texDay.TexFile   = "Data\\textures\\sky\\cloudsclear02.dds";
	SP.texNight.TexFile = "Data\\textures\\sky\\cloudsclear02.dds";
//	SP.uiNumTextures = 1;
	SP.uiSides	   = 16;
	SP.uiSlices    = 16;
	SP.vPosition   = crVec3( 0.f, -500.f, 0.f );
	Sky.Create( SP );

	//Model.LoadFromFile("Data\\models\\female\\female2.3ds", "Data\\models\\female\\");
	Model.LoadFromFile("Data\\models\\monsters\\monster1.3ds", "Data\\textures\\monsters\\");
//	Model.LoadFromFile("Data/models/buildings/gazebo.3ds", 
//					   "Data/textures/humans/dwarf/");
	Model.SetShader( "Data/shaders/Lighting3ds.txt" );
	
	Water1 = new crWater();
	crWaterParams_t wp;
	wp.fScale = 20.0f;
	wp.iHeight = 10;
	wp.iWidth = 10;
	wp.v3Center = crVec3(-0.f, 1.f, -0.f);
//	Water1->CreateGeometry(wp);

	crHeightmapParams_t hm;
	hm.fileName = "Data/maps/lof.bmp";
	hm.tBase.fileName = "Data/textures/walls/stonewall01.dds";
	hm.tBase.s = 25.0f;
	hm.tBase.t = 25.0f;
	hm.tNormal.fileName = "Data/textures/walls/stonewall01_n.dds";
	hm.tNormal.s = 25.0f;
	hm.tNormal.t = 25.0f;
	hm.vOffset = crVec3(0.f, 0.f, 0.0f);
	hm.vScale  = crVec2(1.0f, 1.0f);
	hmap.CreateGeometry( hm );

	lightPos = crVec3(0, 10, 0);
}

/*
========================
    Setup_Game
========================
*/
void crGameLocal::Setup_Game() {
	player.Camera->SetPosition(0, 0, 15);
	player.Camera->Spectate( true );
	player.Spawn();
}


/*
========================
    Setup_Shaders
========================
*/
void crGameLocal::Setup_Shaders() {
/*	shaders[0].LoadVertexShaderFromFile("Data\\shaders\\vert1.txt");
	shaders[0].LoadFragmentShaderFromFile("Data\\shaders\\frag1.txt");
	shaders[0].Link();

	shaders[1].LoadVertexShaderFromFile("Data\\shaders\\vert2.txt");
	shaders[1].LoadFragmentShaderFromFile("Data\\shaders\\frag2.txt");
	shaders[1].Link();

	shaders[2].LoadVertexShaderFromFile("Data\\shaders\\vert3.txt");
	shaders[2].LoadFragmentShaderFromFile("Data\\shaders\\frag3.txt");
	shaders[2].Link();*/
}

/*
========================
    Setup_OGL_classes
========================
*/
void crGameLocal::Setup_OGL_classes() {
	//text1.build("Tahoma", 20);

	HDC a = *renderDevice->InitOptions.hDeviceContext;
		//wglGetCurrentDC();
	/*crFontStyle_t fontStyle;
	 fontStyle.bBold = false; 
	 fontStyle.bItalic = false;
	 fontStyle.bStrikeOut = false;
	 fontStyle.bUnderline = false;
	 fontStyle.fColor[0] = 0.2f;
	 fontStyle.fColor[1] = 0.3f;
	 fontStyle.fColor[2] = 0.8f;
	 fontStyle.fColor[3] = 1.0f;
	 fontStyle.Fontname = "Tahoma";
	 fontStyle.iSize = 20;
	 fontStyle.hDC = wglGetCurrentDC();

	font.InstallFont("Data/fonts/Pulse.ttf");
	font.Create( fontStyle );
	*/	
	SelectObject(a, GetStockObject(SYSTEM_FONT));
//	if(!wglUseFontBitmaps(a, 32, 96, 1000)) MSGBOX("AA");
}

/*
========================
    Shutdown
========================
*/
void crGameLocal::Shutdown() {

	delete  Water1;

	DefaultShutdown();
	ChangeDisplaySettings(NULL, CDS_FULLSCREEN);
}

/*
========================
	HandleMessage
========================
*/
void crGameLocal::HandleMessage( unsigned int msg, WPARAM wParam, LPARAM lParam ) {
	DefaultHandleMessage(msg, wParam, lParam);
}



