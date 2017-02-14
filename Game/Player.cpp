#include "player.h"


crPlayer::crPlayer() {
	Kill();
	Bounds.y = PLAYER_DEFAULT_HEIGHT;
	Camera = new crPlayerCamera( 0.3f );
	Camera->SetPosition(0.0f, Bounds.y, 0.0f);
}

crPlayer::~crPlayer( void ) {
	delete Camera;
}

void crPlayer::Spawn( void ) {
	Alive = true;
}

void crPlayer::Kill( void ) {
	Alive = false;
}

void crPlayer::Render( void ) {
	if (Health <= 0) Kill();
}

void crPlayer::UpdateLook( void ) {
	Camera->CheckMouse( SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	Camera->Look();
}