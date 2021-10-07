#include "shape.h"

//used to render sphere and cylinder 
void Shape::renderQuad(std::vector<std::vector<float>> a, GLuint texture)
{
	
	glBindTexture(GL_TEXTURE_2D, texture);	//binds the texture
	//enable arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//hands the data to the arrays 
	glVertexPointer(3, GL_FLOAT, 0, a[0].data());
	glNormalPointer(GL_FLOAT, 0, a[1].data());
	glTexCoordPointer(2, GL_FLOAT, 0, a[2].data());

	//gets the number to render
	int numbertoRender = a[3][0];
	glDrawArrays(GL_QUADS, 0, numbertoRender);

	//disables arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, NULL);	//render is done no longer need to bind texture makes sure than nothing else will reseve it

}

//used to render disk
//similar as above
void Shape::renderTriangle(std::vector<std::vector<float>> a, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);		//binds the texture

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, a[0].data());
	glNormalPointer(GL_FLOAT, 0, a[1].data());
	glTexCoordPointer(2, GL_FLOAT, 0, a[2].data());

	int numbertoRender = a[3][0];
	glDrawArrays(GL_TRIANGLES, 0, numbertoRender);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, NULL);
}


//can specify resolution and size
std::vector<std::vector<float>> Shape::disk(float seg, float r)
{

	angle = 0;
	int d = 2 * r;
	//temp vectors used to add to the main vector
	std::vector<float> diskVer;
	std::vector<float> diskNorm;
	std::vector<float> diskTex;
	std::vector<float> diskCount;
	//main vector
	std::vector<std::vector<float>> wholeDisk;
	

	//loops for the number of segments sorta like resolution
	for(int i = 0; i < seg; i++)
	{

		//samples the very middle of the circle which i have based around 0, add the coords to the vector
		diskVer.push_back(0);
		diskVer.push_back(0);
		diskVer.push_back(0);


		//adds the normals to the tem normal vector
		diskNorm.push_back(0);
		diskNorm.push_back(0);
		diskNorm.push_back(1);

		//sets up textal coords
		texX = 0.5;
		texY = 0.5;
		//adds them to the temp vector
		diskTex.push_back(texX);
		diskTex.push_back(texY);
				
		//increase coords so it goes to the first sample point 
		X = r * cos(angle);
		Y = r * sin(angle);
			//adds coords to tem vector
		diskVer.push_back(X);
		diskVer.push_back(Y);
		diskVer.push_back(0);

		//adds norms to temp vector
		diskNorm.push_back(0);
		diskNorm.push_back(0);
		diskNorm.push_back(1);

		//calculate new tex coords
		texX = (cos(angle) / d) + 0.5;
		texY = (sin(angle) / d) + 0.5;
		//adds them 
		diskTex.push_back(texX);
		diskTex.push_back(texY);
		
		//increase angle new sample point
		angle += (2 * PI) / seg;
		X = r * cos(angle);
		Y = r * sin(angle);

		//add to temp verts vector
		diskVer.push_back(X);
		diskVer.push_back(Y);
		diskVer.push_back(0);

		// add to temp norm vector
		diskNorm.push_back(0);
		diskNorm.push_back(0);
		diskNorm.push_back(1);

		//calculate new tex coords
		texX = (cos(angle) / d) + 0.5;
		texY = (sin(angle) / d) + 0.5;

		//adds them to vector
		diskTex.push_back(texX);
		diskTex.push_back(texY);			
	}
	//this is how many indicies must be rendered
	diskCount.push_back(seg * 3);

	//add all temp vectors to thge main vector
	wholeDisk.push_back(diskVer);
	wholeDisk.push_back(diskNorm);
	wholeDisk.push_back(diskTex);
	wholeDisk.push_back(diskCount);
	
	//return whole vector
	return wholeDisk;
}


std::vector<std::vector<float>> Shape::sphere(float seg, float r)
{

	float texInc = (1 / seg);

	//set up temp vectors for verticies, normals, and texture coords
	std::vector<float> sphereVer;
	std::vector<float> sphereTex;
	std::vector<float> sphereNorm;

	//vecor to store the number of quads only one item will be stored but will allow me to just pass one item to the functio to render
	std::vector<float> count;

	std::vector<std::vector<float>> wholeSphere;

	//set up angle
	theta = 0;
	delta = 0;
	thetaInc = (2 * PI) / seg;
	deltaInc = PI / seg;	
	

	//loops for the number of segments specified
	for (int i = 0; i<seg; i++)
	{
		texX = 0;
		//loop again for number of sgments
		for (int j = 0; j<seg; j++)
		{
			X = r * cos(theta)*sin(delta);	//calculate x coord
			sphereVer.push_back(X);	//push it to the temp vector
			Y = r * cos(delta);	//calculate y coord
			sphereVer.push_back(Y);	//push to temp
			Z = r * sin(theta) * sin(delta);	
			sphereVer.push_back(Z);

			//set up norms
			sphereNorm.push_back(X / r);
			sphereNorm.push_back(Y / r);
			sphereNorm.push_back(Z / r);

			//set textures
			sphereTex.push_back(texX);
			sphereTex.push_back(texY);
						
			//set up new coords
			X = r * cos(theta + thetaInc)*sin(delta);
			sphereVer.push_back(X);
			Y = r * cos(delta);
			sphereVer.push_back(Y);
			Z = r * sin(theta + thetaInc) * sin(delta);
			sphereVer.push_back(Z);
			
			//set up norms
			sphereNorm.push_back(X / r);
			sphereNorm.push_back(Y / r);
			sphereNorm.push_back(Z / r);
			
			//set textures
			sphereTex.push_back(texX + texInc);
			sphereTex.push_back(texY);
			

			//set up new coords
			X = r * cos(theta + thetaInc)*sin(delta + deltaInc);
			sphereVer.push_back(X);
			Y = r * cos(delta + deltaInc);
			sphereVer.push_back(Y);
			Z = r * sin(theta + thetaInc) * sin(delta + deltaInc);
			sphereVer.push_back(Z);			

			//set up norms
			sphereNorm.push_back(X / r);
			sphereNorm.push_back(Y / r);
			sphereNorm.push_back(Z / r);
			
			//set textures
			sphereTex.push_back(texX + texInc);
			sphereTex.push_back(texY + texInc);


			//set up new coords
			X = r * cos(theta)*sin(delta + deltaInc);
			sphereVer.push_back(X);
			Y = r * cos(delta + deltaInc);
			sphereVer.push_back(Y);
			Z = r * sin(theta) * sin(delta + deltaInc);
			sphereVer.push_back(Z);		

			//set up norms
			sphereNorm.push_back(X / r);
			sphereNorm.push_back(Y / r);
			sphereNorm.push_back(Z / r);
		
			//set textures
			sphereTex.push_back(texX);
			sphereTex.push_back(texY + texInc);

			//increase values as we move a long the x axis
			theta += thetaInc;
			texX += texInc;			
		}

		theta = 0.0f;
		//reset angle been around 
		//increase y values
		delta += deltaInc;
		texY += texInc;
	}


	texY = 0;
	indices = seg * seg * 4;
	count.push_back(indices);
	//add temp vectors to the main vector
	wholeSphere.push_back(sphereVer);
	wholeSphere.push_back(sphereNorm);
	wholeSphere.push_back(sphereTex);
	wholeSphere.push_back(count);

	return wholeSphere;
}

//creates a cylinder not capped, heigh how high, seg resolution, r is the radious
std::vector<std::vector<float>> Shape::cylinder(float height, float seg, float r)
{	
	angle = 0;
	Z = 0;
	
	//sets up temp vectors
	std::vector<float> ver;
	std::vector<float> norm;
	std::vector<float> texVec;
	std::vector<float> num;

	//sets up tex coord increase values 
	float texXInc = (1 / seg);
	float texYInc = (1 / height);

	texXInc = 1 / seg;
	texYInc = 1 / height;
	texY = 0;

	//loops for the height
	for(int j = 0; j < height; j++)
	{
		texX = 0;
		
		//loops until it makes a circle
		while (angle < 2 * PI)
		{

			// no need to sample middle straigt tot the edge
			X = r*cos(angle);
			Y = r*sin(angle);
			//add to temp verts vector
			ver.push_back(X);
			ver.push_back(Y);
			ver.push_back(Z);
			//add normals
			norm.push_back(X / r);
			norm.push_back(Y / r);
			norm.push_back(Z / r);
			//add texture coords
			texVec.push_back(texX);
			texVec.push_back(texY);

			//increase sameple angle
			angle += (2 * PI) / seg;
			//increase tex x coord
			texX += texXInc;
			//calculate secong ppoint with new angle
			x1 = r*cos(angle);
			y1 = r*sin(angle);
			//add them 
			ver.push_back(x1);
			ver.push_back(y1);
			ver.push_back(Z);
			//add texture coords
			texVec.push_back(texX);
			texVec.push_back(texY);
			//add norms
			norm.push_back(x1 / r);
			norm.push_back(y1 / r);
			norm.push_back(Z / r);



			//add vert coord
			ver.push_back(x1);
			ver.push_back(y1);
			ver.push_back(Z + 1);	//increase the height

			//add norms 
			norm.push_back(x1 / r);
			norm.push_back(y1 / r);
			norm.push_back((Z + 1) / r);
			
			//add tex coords
			texVec.push_back(texX);
			texVec.push_back(texY + texYInc);	//since increase height


			//add verts
			ver.push_back(X);
			ver.push_back(Y);
			ver.push_back(Z + 1);	//increased height
			//add norms
			norm.push_back(X / r);
			norm.push_back(Y / r);
			norm.push_back((Z + 1) / r);
			//add tex coords
			texVec.push_back(texX - texXInc);
			texVec.push_back(texY + texYInc);

		}
		texY += texYInc;	//looped once around tghe circle need to increase height
		Z++;	//increase z coord by 1
		angle = 0;	//reset angle
	}	

	//set up whole vector
	std::vector<std::vector<float>> wholeCylinder;
	//asdd all temp vvectors 
	wholeCylinder.push_back(ver);
	wholeCylinder.push_back(norm);
	wholeCylinder.push_back(texVec);
	indices = height * seg * 4;
	num.push_back(indices);
	wholeCylinder.push_back(num);

	//return whole vector
	return wholeCylinder;
}


