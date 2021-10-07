#pragma once


#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include "Camera.h"
#include "Input.h"



class Skybox
{
public:
	Skybox(Input* in, Camera* cam);
	~Skybox();
	void update(float dt, float width, float height);
	void render();

protected:
	
	Camera* camera;
	Input* input;

	//skybox texture
	GLuint skybox;
};

