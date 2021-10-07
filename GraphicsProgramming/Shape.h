#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <vector>
#include "Vector3.h"

class Shape
{

	public:
		void renderQuad(std::vector<std::vector<float>> a, GLuint texture);
		void renderTriangle(std::vector<std::vector<float>> a, GLuint texture);

		//shape functions
		std::vector<std::vector<float>> disk(float seg, float r);
		std::vector<std::vector<float>> sphere(float seg, float r);
		std::vector<std::vector<float>> cylinder(float height, float seg, float r);

protected:
			
		float PI = 3.14159265;
		float angle;
		float X;
		float Y;
		float Z;
		float x1;
		float y1;
		float z1;

	

		float theta;
		float thetaInc;
		float delta;
		float deltaInc;
		float latitude;
		float longitude;
		float texX;
		float texY;
		
		float tex;

		int indices;

		
		
		


		

};
#endif 
