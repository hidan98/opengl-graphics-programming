
#include "Skybox.h"


extern float verts[] = { 1.0, -1.0, -1.0, 
						1.0, 1.0, -1.0, 
						-1.0, 1.0, -1.0, 
						-1.0, -1.0, -1.0, 

						1.0, -1.0, 1.0, 
						1.0, 1.0, 1.0, 
						1.0, 1.0, -1.0, 
						1.0, -1.0, -1.0,  

						-1.0f, -1.0f, 1.0f,
						-1.0f, -1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, 1.0f,

						1.0f, -1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f, -1.0f, 1.0f,

						1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, 1.0f,
						1.0f, 1.0f, 1.0f,

						1.0f, -1.0f, -1.0f,
						-1.0f, -1.0f, -1.0f,
						-1.0f, -1.0f, 1.0f,
						1.0f, -1.0f, 1.0f };



extern float texcoords[] = { 0.50, 0.666,
							0.50, 0.35,
							0.250, 0.35,
							0.250, 0.666,

							0.75, 0.666,
							0.75, 0.35,
							0.5, 0.333,
							0.5, 0.666,

							0.0, 0.666,
							0.250, 0.666,
							0.25, 0.35,
							0.0, 0.35,

							0.75, 0.666,
							0.75, 0.35,
							1.0, 0.35,
							1.0, 0.666,

							0.5, 0.35,
							0.25, 0.35,
							0.25, 0.0,
							0.5, 0.0,


							0.5, 0.666,
							0.25, 0.666,
							0.25, 1,
							0.5, 1

};


Skybox::Skybox(Input* in, Camera* cam)
{
	camera = cam;
	camera->update();
	input = in;

	//set up texture
	skybox = SOIL_load_OGL_texture
	(
		"gfx/skybox7.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}


Skybox::~Skybox()
{
}


void Skybox::update(float dt, float width, float height)
{
	camera->mouseMove(dt, width, height);	//gets mouse movemnt

	if (input->isKeyDown('q'))	//rotate left
	{
		camera->rotate(-1, dt);
		camera->update();
	}

	if (input->isKeyDown('e'))	//rotate right 
	{
		camera->rotate(1, dt);
		camera->update();
	}

	if (input->isKeyDown('w'))	//move forward
	{
		camera->fb(1, dt);
		camera->update();
	}

	if (input->isKeyDown('s'))	//move back
	{
		camera->fb(-1, dt);
		camera->update();
	}
	if (input->isKeyDown(32))//move up 
	{
		camera->upDown(1, dt);
		camera->update();
	}
	if (input->isKeyDown(92))//move down	
	{
		camera->upDown(-1, dt);
		camera->update();
	}

	if (input->isKeyDown('z'))	//pitch up
	{
		camera->pitch(1, dt);
		camera->update();
	}
	if (input->isKeyDown('x'))	//pitch down
	{
		camera->pitch(-1, dt);
		camera->update();
	}

}

void Skybox::render()
{
	//enable textureing
	glEnable(GL_TEXTURE_2D);
	//bind texture
	glBindTexture(GL_TEXTURE_2D, skybox);
	//activating trilinear sampaling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	

	glPushMatrix();

	//translate skybox to camera position
	glTranslatef(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ());
	
	//disable depth test
	glDisable(GL_DEPTH_TEST);

	//used to render sybox as it is in vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, verts);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	//draws the skybox
	glDrawArrays(GL_QUADS, 0, 24);

	//deactivates arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//enable depth test
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
}
