#include "ShapeCorner.h"

//this class is just set up to show of the procedualy generated shapes it does not create them


ShapeCorner::ShapeCorner()
{
	//calls generation of shapes
	sphere1 = shape.sphere(20, 1);
	sphere2 = shape.sphere(40, 2);

	disk1 = shape.disk(40, 3);
	disk2 = shape.disk(40, 2);

	cylinder1 = shape.cylinder(10, 20, 1);
	cylinder2 = shape.cylinder(20, 40, 3);


	//set up textures
	crate = SOIL_load_OGL_texture
	(
		"gfx/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


	sun = SOIL_load_OGL_texture
	(
		"gfx/2k_sun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	earth = SOIL_load_OGL_texture
	(
		"gfx/2k_earth_daymap.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


	cat.load("Models/garfield.obj", "gfx/Garfield_DS.png");

	speed = 8;	//how fast can it go?
}


ShapeCorner::~ShapeCorner()
{
}

void ShapeCorner::update(float dt)
{

	rotation += speed * dt;	//i wonder what is roatating 

}

void ShapeCorner::render()
{
	//lighting setup for the corner 
	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 220, 15, 50, 1.0f };	//position light
	glLightfv(GL_LIGHT6, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT6, GL_POSITION, Light_Position);

	
	//used to see where the light is 
	glPushMatrix();
	glTranslatef(220, 15, 50);
	shape.renderQuad(sphere1, NULL);
	glPopMatrix();
	glEnable(GL_LIGHT6);


	//moves the whole scene 
	glPushMatrix();
	glTranslatef(200, 5, 90);


	//rotates it so that cylinderes are the right way
	glRotatef(-90, 1, 0, 0);

	glPushMatrix();
	glTranslatef(20, 5, 0);
	//render sphere with sun texture 
	shape.renderQuad(sphere1, sun);
	glPopMatrix();

	//draws sphere with crate 
	glPushMatrix();
	glTranslatef(25, 5, 0);
	shape.renderQuad(sphere2, crate);
	glPopMatrix();

	//draws cylinder with sun
	glPushMatrix();
	glTranslatef(30, 5, 0);
	shape.renderQuad(cylinder1, sun);
	glPopMatrix();


	//big cylinder
	glPushMatrix();
	glTranslatef(35, 5, 0);
	shape.renderQuad(cylinder2, crate);	//draws the cylinder
	shape.renderTriangle(disk1, crate);	//caps it

	//what cat...
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 2, 0);
	glScalef(0.25, 0.25, 0.25);
	glPushMatrix();
	glRotatef(rotation, 0, 1, 0);
	cat.render();
	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, 20);
	shape.renderTriangle(disk1, crate);	//caps it
	glPopMatrix();
	glPopMatrix();

	//draws disk with eatch
	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 1, 0, 0);
	shape.renderTriangle(disk1, earth);

	glPopMatrix();

	//draws disk with sun
	glPushMatrix();
	glTranslatef(8, 0, 0);
	glRotatef(90, 1, 0, 0);
	shape.renderTriangle(disk2, sun);


	glPopMatrix();
	glDisable(GL_LIGHT6);
	glPopMatrix();

	

	
}
