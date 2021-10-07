
#include "Camera.h"



Camera::Camera(Input* in)
{
	input = in;
	position.set(0, 0, 6);
	speed = 3.0f;

	LookAt.y = 0;
	LookAt.z = 0;
	LookAt.x = 0;
	
	up.x = 0;
	up.y = 1;
	up.z = 0;

	position.x = 100;
	position.y = 10;
	position.z =30;

	PI = 3.14159265;
		
	thetaInc = (2 * PI) / 500;
}


Camera::~Camera()
{
}

void Camera::update()
{

	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw*3.1415 / 180);
	cosP = cosf(Pitch*3.1415 / 180);
	cosR = cosf(Roll*3.1415 / 180);
	sinY = sinf(Yaw*3.1415 / 180);
	sinP = sinf(Pitch*3.1415 / 180);
	sinR = sinf(Roll*3.1415 / 180);

	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.
	LookAt.x = position.x + forward.x;
	LookAt.y = position.y + forward.y;
	LookAt.z = position.z + forward.z;
	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
}

float Camera::getPositionX()
{
	return position.getX();
}

float Camera::getPositionY()
{
	return position.getY();
}

float Camera::getPositionZ()
{
	return position.getZ();
}

float Camera::getLookAtX()
{
	return LookAt.getX();
}

float Camera::getLookAtY()
{
	return LookAt.getY();
}

float Camera::getLookAtZ()
{
	return LookAt.getZ();
}

float Camera::getUpX()
{
	return up.getX();
}

float Camera::getUpY()
{
	return up.getY();
}

float Camera::getUpZ()
{
	return up.getZ();;
}


void Camera::rotate(float direction, float dt)
{
	Yaw += (direction*speed) * dt;

}

void Camera::fb(float direction, float dt)
{

	position.add(forward, dt*speed*direction); //moves camra forward and back 

}

void Camera::upDown(float direction, float dt)
{
	position.add(up, dt*speed*direction);	//moves cam up and down

}

void Camera::pitch(float direction, float dt)
{
	Pitch += (direction*speed) * dt;
}

void Camera::mouseLookAt(float dt, float x, float y)
{
	//controls the camera with the mouse 
	Pitch -= y*dt;
	Yaw += x*dt;
	update();
}

void Camera::rotatePoint(int r, float speed)
{
	
	//uses equation of a circle 
	position.x = r * cos(theta) + 100;	//the plus 100 is due to the scene being shifted 100
	position.z = r * sin(theta);
	position.y = 10;

	theta += thetaInc * speed;
	if (theta > 2 * PI)	//reset theta 
	{
		theta = 0;
	}
	up.x = 0;
	up.y = 1;
	up.z = 0;

	//forces look at
	LookAt.x = 100;
	LookAt.y = 10;
	LookAt.z = 0;
	Yaw = 0;
	Pitch = 0;
	Roll = 0;

}

void Camera::camPoint(Vector3 pos, Vector3 look)
{
	up.x = 0;
	up.y = 1;
	up.z = 0;
	//forces the camera position
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	//forces the camera look at point
	LookAt.x = look.x;
	LookAt.y = look.y;
	LookAt.z = look.z;

	
}
//contols the mouse moment
void Camera::mouseMove(float dt, float width, float height)
{
	glutWarpPointer(width / 2, height / 2);	//forces the mouse pointer to the middle of the screen
	int x = input->getMouseX() - (width / 2);	//
	int y = input->getMouseY() - (height / 2);
	mouseLookAt(dt, x, y);	//cals function handing the values

}
