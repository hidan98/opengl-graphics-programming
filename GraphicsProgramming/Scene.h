// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "Shape.h"
#include "Model.h"
#include "SolarSystem.h"
#include "Skybox.h"
#include "MirrorLand.h"
#include <math.h>
#include "Plane.h"
#include "SphereLight.h"
#include "ShapeCorner.h"


class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];
	Camera camera;



	GLuint myTexture;


	//diffrent areas of the scene 
	SolarSystem system;
	Skybox box;
	MirrorLand mirror;
	ShapeCorner shapeCorner;
	Plane ground;
	SphereLight sphere;

	//used for fixed cam
	Vector3 lookAt;
	Vector3 goTo;
	//camera bools
	bool cam1;
	bool cam2;
	bool cam3;
	bool cam4;

	Model thomas;
	
	bool wireFrame;


};

#endif