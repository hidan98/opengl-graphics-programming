#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
class Plane
{
public:
	Plane();
	~Plane();

	void render();

protected:
	//ground texture
	GLuint ground;
};

