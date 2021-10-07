#include "SolarSystem.h"


static GLfloat floorVerts[] = { -100.f, -1.f, -100.f, //top left
							-100.f, -1.f, 100.f, // bottom left
							100.f, -1.f, 100.f, //bottom right
							100.f, -1.f, -100.f };// top right






SolarSystem::SolarSystem(Input* in)
{

	//load in models with there textures
	earth.load("Models/largeSphere.obj", "gfx/2k_earth_daymap.jpg");
	moon.load("Models/smallSphere.obj", "gfx/2k_moon.jpg");
	sun.load("Models/largeSphere.obj", "gfx/2k_sun.jpg");
	jupiter.load("Models/largeSphere.obj", "gfx/2k_jupiter.jpg");
	thatsNoMoon.load("Models/Death_Star.obj", "gfx/Death_Star_D.tga");
	spaceShip.load("Models/spaceship.obj", "gfx/spaceship.jpg");
	scoob.load("Models/Scooby-Doo.obj", "gfx/cgang002.png");
	baby.load("Models/BigBaby.obj", "gfx/01___Default.png");


	input = in;;

	speed = 10;	//set speed of the solar system
	startRotation = true;	//makes sure it starts rotating
	lightOff = true;	//makes sure the light is on
	glEnable(GL_LIGHT3);
	
}



SolarSystem::~SolarSystem()
{
}


void SolarSystem::update(float dt)
{
	if (startRotation)	//if rotation is on. if not this will not be trigured and it will not rotate 
	{
		rotation += speed *dt;	//controls rotation of solar system
	}

	//toggles rotation
	if (input->isKeyDown('p'))
	{
		input->SetKeyUp('p');
		if (startRotation)
		{
			startRotation = false;
		}
		else
		{
			startRotation = true;
		}
		
	}

	//toggles lights
	if (input->isKeyDown('l'))
	{
		input->SetKeyUp('l');
		if (lightOff)
		{
			lightOff = false;
		}
		else if (!lightOff)
		{
			lightOff = true;
		}
	}

}

void SolarSystem::render()
{

	//shows where the light is coming from
	glPushMatrix();
	glTranslatef(-30, 60, 0);
	moon.render();
	glPopMatrix();


	//GLfloat Light_Ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { -30.0f, 60.0f, 0.0f, 1.0f };
	GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

	

	
	//glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 52.0f);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 1.0);	//intense spot
	
	shadow.generateShadowMatrix(shadowMatrix, Light_Position, floorVerts);	//creates shadow matrix 


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//only render shadows if the light is on 
	if (lightOff)
	{
		glColor3f(0.1f, 0.1f, 0.1f); // Shadow's colour

		glPushMatrix();	//push sun
		glMultMatrixf((GLfloat *)shadowMatrix);
		//translate to floor and draw shadow, remember to match any transforms on the object
		glTranslatef(-30.f, 13.0f, 0.f);
		glScalef(3.0f, 3.0f, 3.0f);
		sun.render();


		glPushMatrix();
		glRotatef(rotation / 2, 0, 1, 0);
		glPushMatrix();
		glTranslatef(-10, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glRotatef(rotation, 1, 1, 0);
		baby.render();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();	//push earth
		glRotatef(rotation / 2, 0, 1, 0);
		glTranslatef(10, 0, 0);
		glScalef(0.2, 0.2, 0.2);
		earth.render();

		glPushMatrix();	//push moon

		glRotatef((rotation * 2), 0, 1, 0);
		glTranslatef(5, 0, 0);
		glScalef(1, 1, 1);
		moon.render();
		glPopMatrix();	//pop moon

		glPopMatrix();	//pop earth

		glPushMatrix();	//pop juputer

		glRotatef((rotation / 5), 0, 1, 0);
		glTranslatef(15, 0, 0);
		glScalef(0.3, 0.3, 0.3);
		jupiter.render();

		glPushMatrix();	//pop deathstar
		glRotatef((rotation / 4), 0, 1, 0);
		glTranslatef(10, 0, 0);
		glScalef(0.5, 0.5, 0.5);
		thatsNoMoon.render();

		glPushMatrix();	//push spaceship
		glRotatef((rotation / 3), 0, 1, 0);
		glTranslatef(6, 0, 0);
		glScalef(0.7, 0.7, 0.7);
		spaceShip.render();

		glPopMatrix();	//pop spaceship

		glPopMatrix();	//pop seathstar



		glPopMatrix();	//pop jupiter

		glPopMatrix();	//pop sun

	}

	glColor3f(1.0f, 1.0f, 1.0f);	//reset light value
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	
	//in order to toggle lighting on and off
	if (!lightOff)
	{
		glDisable(GL_LIGHT3);
	}
	else
	{
		glEnable(GL_LIGHT3);
	}

	


	//Mini solar system type thing

	//the sun
	glPushMatrix();
	//moves whole soalar system
	glTranslatef(-30.0f, 13.0f, 0.f);
	glScalef(3.0f, 3.0f, 3.0f);
	sun.render();

	//everything else is in the same matrix as the sun
		glPushMatrix();
		scoob.render();	//so thats what powers the sun 
		glPopMatrix();

		glPushMatrix();
		glRotatef(rotation / 2, 0, 1, 0);

			glPushMatrix();
			glTranslatef(-10, 0, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(rotation, 1, 1, 0);
			baby.render();
			glPopMatrix();
		glPopMatrix();

	

	//earth
		glPushMatrix();
		glRotatef(rotation / 2, 0, 1, 0);
		glTranslatef(10, 0, 0);
		glScalef(0.2, 0.2, 0.2);
		earth.render();

		//push moon
			glPushMatrix();
			glRotatef((rotation * 2), 0, 1, 0);
			glTranslatef(5, 0, 0);
			glScalef(1, 1, 1);
			moon.render();
			glPopMatrix();	//pop moon

		glPopMatrix();	//pop earth

	//push jupiter
		glPushMatrix();
		glRotatef((rotation / 5), 0, 1, 0);
		glTranslatef(15, 0, 0);
		glScalef(0.3, 0.3, 0.3);
		jupiter.render();

		// push deathstar
			glPushMatrix();
			glRotatef((rotation / 4), 0, 1, 0);
			glTranslatef(10, 0, 0);
			glScalef(0.5, 0.5, 0.5);
			thatsNoMoon.render();

			// push spaceship
				glPushMatrix();
				glRotatef((rotation / 3), 0, 1, 0);
				glTranslatef(6, 0, 0);
				glScalef(0.7, 0.7, 0.7);
				spaceShip.render();
				glPopMatrix();	//pop spaceship

			glPopMatrix();	//pop deathstar

		glPopMatrix();	//pop jupiter

	glPopMatrix();	//pop sun




}
