#pragma once
#include "Vector3.h"
#include <math.h>
#include "glut.h"
#include "Input.h"
class Camera
{
public:
	Camera(Input* cam);
	~Camera();

	void update();


	float getPositionX();
	float getPositionY();
	float getPositionZ();

	float getLookAtX();
	float getLookAtY();
	float getLookAtZ();


	float getUpX();
	float getUpY();
	float getUpZ();

	void rotate(float direction, float dt);
	void fb(float direction, float dt);
	void upDown(float direction, float dt);
	void pitch(float direction, float dt);
	void rotatePoint(int r, float speed);
	void mouseLookAt(float dt, float x, float y);
	void camPoint(Vector3 Pos, Vector3 look);
	void mouseMove(float dt, float width, float height);

protected:
	Vector3 position;
	Vector3 LookAt;
	Vector3 up;
	Vector3 forward;

	float Yaw, Pitch, Roll;

	float speed;
	float theta;
	float thetaInc;
	float PI;
	Input* input;

};

