#include "Plane.h"



Plane::Plane()
{
	//set up floor texture 
	ground = SOIL_load_OGL_texture
	(
		"gfx/trak2_plate2a.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}


Plane::~Plane()
{
}

void Plane::render()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground);
	//enable Trilinear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	//begin drawing plane
	glBegin(GL_QUADS);

	//loops 200 times
	for (int z = 100; z > -100; z--)
	{
		//loops 350 times
		for (int x = -100; x < 250; x++)
		{
			
			glTexCoord2f(0, 0);		//sets first tex coord
			glNormal3f(0, -1, 0);	//sets normal to negative since i am rotating it in the main scene 
			glVertex3f(x, -1, z);	//sets first virtex

			//repeat above
			glTexCoord2f(1, 0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 1, -1, z);

			glTexCoord2f(1, 1);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 1, -1, z + 1);

			glTexCoord2f(0, 1);
			glNormal3f(0, -1, 0);
			glVertex3f(x, -1, z + 1);
		}

	}

	glEnd();
}
