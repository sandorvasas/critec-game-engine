// Copyright (C) 2007 by Sandor Vasas
//
#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "../Critec/Core.h"
#pragma hdrstop

#define PLAYER_DEFAULT_HEIGHT		2.0f


class crPlayer {
public:
	crPlayerCamera*		Camera;
	//MODEL				model;

	bool				Alive;
	unsigned int		Health;
	unsigned int		Armor;
	crVec3				Bounds;
	bool				inAir;

public:
						crPlayer( void );
						~crPlayer( void );

	void				Spawn( void );
	void				Kill( void );
	void				Render( void );
	void				UpdateLook( void );
};

#endif