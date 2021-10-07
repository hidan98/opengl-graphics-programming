#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Model.h"
class MirrorLand
{
public:
	MirrorLand();
	~MirrorLand();
	void render();
	void update(float dt);
	

protected:


	Model model;
	Model model1;
	Model model2;

	float rotate;
	 float speed;
};

