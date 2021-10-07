#include "MirrorLand.h"


MirrorLand::MirrorLand()
{

	model.load("models/teapot.obj", "gfx/crate.png");	//load in teapot model

	speed = 10;	//set the speed of rottion
}


MirrorLand::~MirrorLand()
{
}


void MirrorLand::update(float dt)
{
	rotate += speed * dt;	//controls the rotating teapots
}


void MirrorLand::render()
{
	
	glPushMatrix();
	//translate whole section of the scene 
	glTranslatef(100, 10, 0);

	
	glPushMatrix();

	//teapot on top of the mirror represents where the light is coming from
	glPushMatrix();
	glTranslatef(-3, 30, 0);
	glScalef(0.25, 0.25, 0.25);
	model.render();
	glPopMatrix();


	glPushMatrix();
	//set light position since it is directional
	glTranslatef(-3, 30, 0);
	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 0.0f, 1.0f, 1.0f };	//that lovely magenta colour 'tis bliss

	GLfloat Light_Position[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position);

	glPopMatrix();
	glEnable(GL_LIGHT2);

	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);	//stops writing to the frame buffer
	glEnable(GL_STENCIL_TEST);	//enable stencil test
	glStencilFunc(GL_ALWAYS, 1, 1);	//set function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);	//set stencil opperater to always pass
	glDisable(GL_DEPTH_TEST);	//disable depth test

	glEnable(GL_CULL_FACE);	//enable cull face
	glCullFace(GL_BACK);	//cull back face
	glBegin(GL_QUADS);	//draws the mirror
	glVertex3f(-20, 20, 0);
	glVertex3f(-20, -20, 0);
	glVertex3f(20, -20, 0);
	glVertex3f(20, 20, 0);
	glEnd();
	glDisable(GL_CULL_FACE);	//disables culling faces

	glEnable(GL_DEPTH_TEST);	//enable depth test

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);	//render to frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);	//stencil op to pass if value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);	//set stencil buffer to keep values
	

	//draws the reflection  
	glPushMatrix();
	glTranslatef(10, 10, -20);
	glScaled(0.25, 0.25, 0.25);
	glRotatef(-rotate, 0, 1, 0);
	model.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 10, -30);
	glScaled(0.75, 0.75, -0.75);
	glRotatef(rotate, -1, 0, 0);
	model.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -20);
	glScaled(0.50, 0.50, 0.50);
	glRotatef(rotate, 0, 0, 1);
	model.render();
	glPopMatrix();


	glDisable(GL_STENCIL_TEST);	//disable test no longer needed

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//sets the blend function

	//draws actual teapots not the reflection 
	glPushMatrix();
	glTranslatef(10, 10, 20);
	glScaled(0.25, 0.25, 0.25);
	glRotatef(rotate, 0, 1, 0);
	model.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 10, 30);
	glScaled(0.75, 0.75, 0.75);
	glRotatef(rotate, -1, 0, 0);
	model.render();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslatef(0, 0, 20);	
	glRotatef(rotate, 0, 0, 1);
	model.render();
	glPopMatrix();

	glEnable(GL_BLEND);	//enabvle blending
	glDisable(GL_LIGHT2);
	glColor4f(0.8f, 0.8f, 1.0f, 0.4f);	//colour of the mirror

	//draw the mirror
	glBegin(GL_QUADS);
	glVertex3f(-20, 20, 0);
	glVertex3f(-20, -20, 0);
	glVertex3f(20, -20, 0);
	glVertex3f(20, 20, 0);
	glEnd();
	
	glDisable(GL_BLEND);	//stop blending 	
	
	glPopMatrix();
	
	glPopMatrix();

	glDisable(GL_LIGHT2);	//turn of lighting

}
