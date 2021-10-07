#include "Scene.h"

Scene::Scene(Input *in) : system(in), box(in, &camera), sphere(in), camera(in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Other OpenGL / render setting should be applied here.
	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	
	myTexture = SOIL_load_OGL_texture
	(
		"gfx/2k_sun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	
	//model set up
	
	thomas.load("models/thomas.obj", "gfx/COMMON1.png");
	

	// Initialise variables
	glEnable(GL_TEXTURE_2D);


	wireFrame = false;
	
}

void Scene::update(float dt)
{
	// Handle user input

	//camera controls 
	if (input->isKeyDown('1'))
	{
		input->SetKeyUp('1');
		cam1 = true;	//enables came disables the rest
		cam2 = false;
		cam3 = false;
		cam4 = false;
	}
	if (input->isKeyDown('2'))
	{
		input->SetKeyUp('2');
		cam2 = true;//enables came disables the rest
		cam1 = false;
		cam3 = false;
		cam4 = false;
	}

	if (input->isKeyDown('3'))
	{
		input->SetKeyUp('3');
		cam1 = false; //enables came disables the rest
		cam2 = false;
		cam3 = true;
		cam4 = false;

	}
	if (input->isKeyDown('4'))
	{
		input->SetKeyUp('4');
		cam1 = false; //enables came disables the rest
		cam2 = false;
		cam3 = false;
		cam4 = true;

	}

	if (input->isKeyDown('0'))
	{
		cam1 = false;	 //disables all cams free roam
		cam2 = false;
		cam3 = false;
		cam4 = false;
	}



	//activate wire frame
	if (input->isKeyDown('v'))
	{
		
		input->SetKeyUp('v');
		//if the wire frame is not active 
		if (wireFrame)
		{
			glPolygonMode(GL_FRONT, GL_LINE);	//activate wire frame
			wireFrame = false;	//sets bool so next time v is pressed we can diable it 
		}
		else if (!wireFrame)	//if the wire frame is active but wish to disable 
		{
			glPolygonMode(GL_FRONT, GL_FILL);	//disable
			wireFrame = true;	//set bool
		}
	}

	if (cam1)	//camera 1 rotating around teapots 
	{
		camera.rotatePoint(60, dt);	//calls function
	}

	else if (cam2)	//cam 2 pointing at face
	{
		goTo.set(155, 14, -80);
		lookAt.set(200, 14, -80);
		camera.camPoint(goTo, lookAt);
	}
	else if (cam3)	//cam three alows mouse movemnt focus on the spheres
	{
		goTo.set(180, 15, -4);
		lookAt.set(205, 9, -4);
		camera.camPoint(goTo, lookAt);
		camera.mouseMove(dt, width, height);
	}
	else if (cam4)	//lets not discuss this one
	{
		goTo.set(-30.0f, 18.0f, 4.f);
		lookAt.set(-30.0f, 16.0f, 0.f);
		camera.camPoint(goTo, lookAt);
		
	}
	else//if no cam is active the user has free roam	
	{
		box.update(dt, width, height);
	}
	
	
	// update scene related variables.
	system.update(dt);
	sphere.update(dt);
	mirror.update(dt);
	shapeCorner.update(dt);

	
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera

	//sets the look at to be the camera possition look at and up
	gluLookAt(camera.getPositionX(), camera.getPositionY(), camera.getPositionZ(), camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(), camera.getUpX(), camera.getUpY(), camera.getUpZ());
	
		
	// Render geometry/scene here -------------------------------------
	
	glEnable(GL_NORMALIZE);

	//disable lighting dont want my sky box to be effected
	glDisable(GL_LIGHTING);
	box.render();	//render sy box
	glEnable(GL_LIGHTING);
	

	glPushMatrix();
	glTranslatef(180, 1, -80);
	glRotatef(-90, 0, 1, 0);
	glScalef(5, 5, 5);
	thomas.render();	//render train
	glPopMatrix();


	glPushMatrix();
	glRotatef(180, 1, 0, 0);	//rotate the ground so that the front face is facing the right way
	ground.render();			//call the ground render function;
	glPopMatrix();
	
	system.render();	//renders the solar system
	sphere.render();	//render sphere wall
	mirror.render();	//render the teapots showing the mirror
	shapeCorner.render();	//render shape corner

	glDisable(GL_LIGHTING);

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 300.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
