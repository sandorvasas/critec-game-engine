// Copyright (C) 2007 by Sandor Vasas
//
#ifndef __GAME_SKY_H_
#define __GAME_SKY_H_

#include "../Critec/Core.h"
#pragma hdrstop

#define shadFragment_source																							\
	"uniform sampler2D SkyTexture; "																				\
	"uniform sampler2D NightTexture;"																				\
	"uniform float Time;"																							\
	"void main() { "																								\
	"  crVec4 texSky = texture2D(SkyTexture, gl_TexCoord[0].st);"														\
	"  crVec4 texNight = texture2D(NightTexture, gl_TexCoord[0].st);"													\
	"  crVec4 fragColor = texNight;"																					\
	" if (Time > 100.0) "																							\
	"  fragColor = fragColor * max(0.0, (1.0-(Time - 100.0)/1000.0)) + texNight * min(1.0, ((Time - 100.0)/1000.0));"	\
	" gl_FragColor = fragColor;"																					\
	"}"

#define shadVertex_source							\
	"void main() {"									\
	"  gl_Position = ftransform();"					\
	"  gl_TexCoord[0].st = gl_MultiTexCoord0.st;"	\
	"}"	


class crSkyDome {
protected:
	crVec3					Position;
	crArray<crVec3>			aVertex;
	crArray<crVec2>			aTexCoord;
	crArray<unsigned short> aIndex;
	unsigned int			SkyTexture,
							NightTexture;
	unsigned int			Sides;
	unsigned int			Slices;
	crGLSLShader			Shader;

public:
							crSkyDome( void );
	virtual					~crSkyDome( void );

	void					Create( float size, float sFactor, unsigned int Sides, unsigned int Slices, unsigned int SkyTexture, unsigned int NightTexture );
	virtual void			Destroy( void );
	void					ChangeTexture( unsigned int SkyTexture );
	void					ChangePosition( float x, float y, float z );
	void					ChangePosition( crVec3 Position );
	void					Render( float dayTime=0 );
};	



//================================
//  crSkyDome short functions
//================================
inline void crSkyDome::ChangeTexture ( unsigned int SkyTexture ) {
	this->SkyTexture = SkyTexture;
}

inline void crSkyDome::ChangePosition ( float x, float y, float z ) {
	Position = crVec3(x, y, z);
}

inline void crSkyDome::ChangePosition ( crVec3 Position ) {
	this->Position = Position;
}


#endif