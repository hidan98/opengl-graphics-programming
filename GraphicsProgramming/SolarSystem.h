#pragma once
#include "Model.h"
#include "Input.h"
#include "Shadow.h"
class SolarSystem
{
public:
	SolarSystem(Input* in);
	~SolarSystem();

	void update(float dt);
	void render();

protected:

	// all the diffrent models
	Model earth;
	Model moon;
	Model sun;
	Model jupiter;
	Model thatsNoMoon;
	Model spaceShip;
	Model baby;
	Model scoob;
	Input* input;

	Shadow shadow;

	float shadowMatrix[16];
	//rotation
	float speed;
	float rotation;
	//toggle bools
	bool startRotation;
	bool lightOff;
};

