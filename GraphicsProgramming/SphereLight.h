#pragma once
#include "Shape.h"
#include <vector>
#include "Input.h"
#include "Vector3.h"

class SphereLight
{
public:
	SphereLight(Input* in);
	~SphereLight();

	void update(float  dt);
	void render();

protected:
	Shape shape;
	std::vector<std::vector<float>> sphere;;

	Input* input;
	Vector3 position;
	float speed;
	
	
};




