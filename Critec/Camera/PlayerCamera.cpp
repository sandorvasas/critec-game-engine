#include "PlayerCamera.h"

crPlayerCamera::crPlayerCamera( void ) {
	Initialize();
}

crPlayerCamera::crPlayerCamera( float rad ) {
	bounds.x = rad;
	Initialize();
}

crPlayerCamera::~crPlayerCamera( void ) {
}

void crPlayerCamera::Initialize( void ) {
	Velocity  = 4.f;
	playerHeight= 3.0f;
	Position  = crVec3( 0.f, playerHeight, 0.f );
	degPitch  = 0.f;
	degYaw	  = 0.f;
	degHeading = 0.f;
	MaxPitch	=  90.0f;
	MinPitch	= -90.0f;
	MaxYaw		=  90.0f;
	MinYaw		= -90.0f;
	MouseSpeed  = 0.2f;
	counter     = 0.0f;
	isSpectating = false;
	isJumping = false;
	isCrawling = false;
	isCrouching = false;
	isRunning = false;
	boundPoints[0] = crVec3(1.0f, 0.0f, 0.0f);
	boundPoints[1] = crVec3(0.0f, 0.0f, 1.0f);
	boundPoints[2] = crVec3(0.0f, playerHeight, 0.0f);
	boundPoints[3] = crVec3(0.5f, 0.0f, 0.5f);
	boundPoints[4] = crVec3(-0.5f, 0.0f, 0.5f);
}

void crPlayerCamera::ChangePitch( float degrees ) {
	degPitch += degrees;
	if(degPitch > MaxPitch) degPitch = MaxPitch;
	if(degPitch < MinPitch) degPitch = MinPitch;
}

void crPlayerCamera::ChangeHeading( float degrees ) {
	degHeading += degrees;
}

void crPlayerCamera::ChangeYaw( float degrees ) {
	degYaw += degrees;
	if(degYaw > MaxYaw) degYaw = MaxYaw;
	if(degYaw < MinYaw) degYaw = MinYaw;
}

void crPlayerCamera::Step( float forward, float strafe, float ud ) {
	crVec3 View = ((isSpectating)?Direction:mv) - Position;
	float x, z, V = Velocity;

	if (isRunning)	V *= 3.0f;
	if (isSpectating) V *= 3.0f;

	forward *= V;
	strafe *= V;
	ud *= Velocity;

	// FORWARD
	x = View.x * forward;
	z = View.z * forward;
	Direction.x += x;
	if(isSpectating) Direction.y += View.y * forward;
	Direction.z += z;

	Position.x  += x;
	if(isSpectating) Position.y += View.y * forward;
	Position.z  += z;

	if(isSpectating) return;

	// STRAFE
	crVec3 OView = View.GetOrthoXZ();
	x = OView.x * strafe;
	z = OView.z * strafe;
	Direction.x += x;
	Direction.z += z;

	Position.x  += x;
	Position.z  += z;

	// UP-DOWN
	Direction.y += ud;
	Position.y  += ud;

	
	if (isSpectating) return;

	counter += 0.2f;
	if(isRunning) counter += 0.1f;
}

void crPlayerCamera::Look( void ) {
	crMat4 matrix;

	Pitch.CreateFromEulerAngles(degPitch, 0.0f, 0.0f);
	Heading.CreateFromEulerAngles(0.0f, degHeading, 0.0f);
	Yaw.CreateFromEulerAngles(0.0f, 0.0f, degYaw);

	crVec3 cPos = Position;

	if(!isSpectating) {

		if(!isJumping) 
			cPos.y +=  sinf(counter)*0.2f;

		if(isCrouching) 
			Position.y -= playerHeight*(2.0f/3.0f);

		if(isCrawling)
			Position.y -= playerHeight*(5.0f/6.0f);

	}

	(Pitch*Heading).CreateMatrix( matrix.ToFloatPtr() );
	matrix.Translate(-cPos);
	renderDevice->SetTransform(TRANSFORM_MULT, matrix.ToFloatPtr());

	Pitch.CreateMatrix( matrix.ToFloatPtr() );
	Direction.y = matrix[9];

	(Heading*Pitch).CreateMatrix( matrix.ToFloatPtr() );
	Direction = Position + crVec3( matrix[8], Direction.y, -matrix[10]) * Velocity;

	Heading.CreateMatrix( matrix.ToFloatPtr() );
	mv = Position + crVec3(matrix[8],  matrix[9], -matrix[10]) * Velocity;
	
	Frustum.Update();
}

void crPlayerCamera::CheckMouse(int mx, int my) {
	POINT CursorPos;
	GetCursorPos(&CursorPos);
	if (CursorPos.x == mx && CursorPos.y == my) return;

	if (CursorPos.x != mx) ChangeHeading( -(mx - CursorPos.x) * MouseSpeed );
	if (CursorPos.y != my) ChangePitch  ( -(my - CursorPos.y) * MouseSpeed );

	SetCursorPos( mx, my );
}

void crPlayerCamera::Jump( void ) {
	if(isSpectating || isJumping) return;
	isJumping = true;
	isCrawling = false;
	isCrouching = false;

	jmpStartTime = (float)GetTickCount();
	jmpPosy = Position.y;
}

void crPlayerCamera::Crouch( bool x ) {
	if(isSpectating) return;
	if(x && !isCrouching) {
		isCrouching = true;
		isRunning = false;
		isCrawling = false;
	}
	else if( !x && isCrouching ) isCrouching = false;
}

void crPlayerCamera::Run( bool x ) {
	if(isSpectating) return;
	if(x && !isRunning) {
		isRunning = true;
		isCrouching = false;
		isCrawling = false;
	}
	else if(!x && isRunning ) isRunning = false;
}

void crPlayerCamera::Crawl( bool x ) {
	if(isSpectating) return;
	if(x && !isCrawling) {
		isCrawling = true;
		isRunning = false;
		isCrouching = false;
	}
	else if( !x && isCrawling ) isCrawling = false;
}

void crPlayerCamera::Spectate( bool x ) {
	isSpectating = x;
}

void crPlayerCamera::ApplyGravity( void ) {
	if(isSpectating) return;
	if(!isJumping) {
		Position.y -= GFORCE/2.0f;
		Direction.y -= GFORCE/2.0f;
	}
	else {
		float d = (GetTickCount() - jmpStartTime);
		float h = (sinf(PI/2+d/540.0f))*4.0f;
		Position.y  = Position.y  - GFORCE/2.0f + h;
		Direction.y = Direction.y - GFORCE/2.0f + h;
		if (d>PI*270.0f) isJumping = false;
	}
}