#include "SphereLight.h"



SphereLight::SphereLight(Input* in)
{
	sphere = shape.sphere(20, 1);	//generate a sphere
	input = in;
	//set up position of the light
	position.x = 185;
	position.y = 9;
	position.z = -4;
	//speed of the light moving
	speed = 5;
}


SphereLight::~SphereLight()
{
}

void SphereLight::update(float dt)
{
	//controlls the movment of the light
	if (input->isKeyDown(','))
	{
		position.z -= speed * dt;
	}
	if (input->isKeyDown('.'))
	{
		position.z += speed * dt;

	}
}

void SphereLight::render()
{

	//set up light atributes 
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_colour[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 50 };
	GLfloat high_shininess[] = { 100 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

	GLfloat Light_Specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { position.x, position.y, position.z, 1.0f };	//moves the light 

	//set up the light
	glLightfv(GL_LIGHT5, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Light_Specular);
	glLightfv(GL_LIGHT5, GL_POSITION, Light_Position);


	glEnable(GL_LIGHT5);
	//sphere representing where the light is
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	shape.renderQuad(sphere, NULL);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 0, 0);

	////////////////////// first layer
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glColor3f(1, 0, 0);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5, -4);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5, -8);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();
	///////////////////////////////////////	second layer

	glPushMatrix();
	glTranslatef(0, 9, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(0, 1, 0);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 9, -4);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 9, -8);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();
	//////////////////////////////// thrid layer

	glPushMatrix();
	glTranslatef(0, 13, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColor3f(1, 0, 1);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 13, -4);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 13, -8);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	shape.renderQuad(sphere, NULL);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glDisable(GL_LIGHT5);
	
	glPopMatrix();
}
