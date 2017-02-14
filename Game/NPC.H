// Copyright(C) 2006-2007 by Sandor Vasas
//

#ifndef __NPC_H_
#define __NPC_H_

#include "player.h"
#include "../Critec/Core.h"
#pragma hdrstop


typedef cr3DSModel			NPCMODEL;
typedef unsigned int   	    NPCTYPE[];

extern NPCTYPE NPC_TYPE_HUMAN;
extern NPCTYPE NPC_TYPE_SOLDIER;
extern NPCTYPE NPC_MONSTER_LEVEL1;
extern NPCTYPE NPC_MONSTER_LEVEL2;
extern NPCTYPE NPC_MONSTER_LEVEL3;
extern NPCTYPE NPC_MONSTER_LEVEL4;


class NPC {
private:
	void		DefCreate		();

public:
	NPCMODEL	Model;
	crPlayer*	Player;

	bool		Alive;
	UINT		Health;
	UINT		Armor;
	crVec3		Position;

	NPC() {};

	void		Create			( NPCTYPE type, crPlayer *player );
	void		Create			( UINT Health, UINT Armor, crPlayer *player );
	//void		Create			( char* NPCstructfilename,  crPlayer *player )  {};


	void		LoadModelFile	( char* modelfilename );
	void		Spawn			( void );
	void		Kill			( void );
	void		SetPosition		( crVec3 newPosition );
	void		Render			( void);
	
};

#endif