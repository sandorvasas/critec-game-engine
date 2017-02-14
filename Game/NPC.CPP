#include "NPC.h"

NPCTYPE	NPC_TYPE_HUMAN				= {100, 0};
NPCTYPE NPC_TYPE_SOLDIER			= {120, 100};
NPCTYPE NPC_MONSTER_LEVEL1			= {100, 0};
NPCTYPE NPC_MONSTER_LEVEL2			= {150, 20};
NPCTYPE NPC_MONSTER_LEVEL3			= {200, 100};
NPCTYPE NPC_MONSTER_LEVEL4			= {400, 200};

void NPC::Create	(NPCTYPE type,  crPlayer *player) {
	this->Health = type[0];
	this->Armor	 = type[1];
	this->Player = player;
	DefCreate();
}

void NPC::Create	(UINT Health, UINT Armor,  crPlayer *player) {
	this->Health = Health;
	this->Armor	 = Armor;
	this->Player = player;
	DefCreate();
}

void NPC::DefCreate() {
}

void NPC::Spawn() {
	Alive = true;
}

void NPC::Kill() {
	Alive = false;
}

void NPC::SetPosition(crVec3 newPosition) {
	Position = newPosition;
}

void NPC::Render() {
	//Model.Render(Position);
}

void NPC::LoadModelFile(char* modelfilename) {
	//Model.Load(modelfilename);
	//Model.FindAABBVertices();
}