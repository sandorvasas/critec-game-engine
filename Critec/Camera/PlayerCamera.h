// Copyright (C) 2007 by Sandor Vasas

#ifndef __CRITEC_PLAYERCAMERA_H__
#define __CRITEC_PLAYERCAMERA_H__

#include "../BD/frustum.h"
#include "../Math/Math3D.h"
#pragma hdrstop

class crFrustum;

class crPlayerCamera {
public:
						crPlayerCamera( void );
	explicit			crPlayerCamera( float rad );
						~crPlayerCamera( void );

	void				ChangePitch( float degrees );
	void				ChangeHeading( float degrees );
	void				ChangeYaw( float degrees );
	void				ChangeVelocity( float Velocity );
	void				Step( float forward, float strafe, float ud );
	void				SetVelocity( float Velocity );
	void				SetPosition( crVec3 Position );
	void				SetPosition( float x, float y, float z);
	void				SetPlayerHeight( float height );
	void				SetMouseSpeed( float MouseSpeed );
	float				GetMouseSpeed( void );
	float				GetVelocity( void );

	void				Look( void );
	void				CheckMouse( int mx, int my);

	void				Jump( void );
	void				Crouch( bool x );
	void				Run( bool x );
	void				Crawl( bool x );
	void				Spectate( bool x=true );

	void				ApplyGravity( void );

protected:
	void				Initialize( void );

protected:
	crQuaternion		Heading;
	crQuaternion		Pitch;
	crQuaternion		Yaw;
	float				degHeading;
	float				degPitch;
	float				degYaw;
	float				MaxYaw;
	float				MinYaw;
	float				MaxPitch;
	float				MinPitch;
	float				Velocity;
	float				MouseSpeed;
	float				playerHeight;
	crVec3				mv;

	float				maxStepHeight;
	float				maxJumpHeight;

	bool				isRunning;
	bool				isJumping;
	bool				isCrouching;
	bool				isCrawling;
	bool				isSpectating;

	float				counter;	
	float				jmpStartTime;
	float				jmpPosy;

public:
	crVec3				bounds;
	crVec3				Position;
	crVec3				Direction;
	crFrustum			Frustum;
	crVec3				boundPoints[5];
};



//=====================================================
// Inline implementation of short functions 
//=====================================================
inline
void crPlayerCamera::ChangeVelocity	( float Velocity ) {
	this->Velocity += Velocity;
}

inline
void crPlayerCamera::SetVelocity( float Velocity ) {
	this->Velocity = Velocity;
}

inline
void crPlayerCamera::SetPosition( crVec3 Position ) {
	crVec3 lP = Position - this->Position;
	this->Direction += lP;
	this->Position += lP;
	this->Position.y += playerHeight;
	this->Direction.y +=playerHeight;
}

inline
void crPlayerCamera::SetPosition( float x, float y, float z) {
	Position = crVec3( x, y, z );
}

inline
void crPlayerCamera::SetMouseSpeed( float MouseSpeed ) {
	this->MouseSpeed = MouseSpeed;
}

inline
void crPlayerCamera::SetPlayerHeight( float height ) {
	playerHeight = height;
	boundPoints[2].y = height;
}

inline
float crPlayerCamera::GetVelocity( void ) {
	return Velocity;
}

inline
float crPlayerCamera::GetMouseSpeed	( void ) {
	return MouseSpeed;
}



#endif