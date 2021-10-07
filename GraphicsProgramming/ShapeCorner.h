#pragma once
#include "Shape.h"
#include <vector>
#include "SOIL.h"
#include "Model.h"
class ShapeCorner
{
public:
	ShapeCorner();
	~ShapeCorner();

	void update(float dt);
	void render();

protected:

	//shape call
	Shape shape;
	//shape vectors
	std::vector<std::vector<float>> sphere1;
	std::vector<std::vector<float>> sphere2;

	std::vector<std::vector<float>> disk1;
	std::vector<std::vector<float>> disk2;

	std::vector<std::vector<float>> cylinder1;
	std::vector<std::vector<float>> cylinder2;


	Model cat;	//who is this...

	//textures
	GLuint crate;
	GLuint sun;
	GLuint earth;

	//i wonder who these are for...
	float rotation;
	float speed;
};

