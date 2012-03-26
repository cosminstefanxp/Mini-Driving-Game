#include "Parallelepiped.h"

// constructor fara parametri ce creaza un paralelipiped cu toate laturile 1
Parallelepiped::Parallelepiped(void) : Object3D(Custom)
{
	length=height=width=1;
	Wireframe = false;
}
// constructor care ia dimensiunile laturilor
Parallelepiped::Parallelepiped(float _length, float _height, float _width) : Object3D(Custom)
{
	this->length=_length;
	this->width=_width;
	this->height=_height;
	this->Wireframe = false;

}

Parallelepiped::~Parallelepiped(void)
{
}

// DRAW
// Suprascriem prin polimorfism functia de desenare a clasei parinte 
// pentru a avea propria functie de desenare
//-------------------------------------------------
void Parallelepiped::Draw ()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
		return;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// setari de material :
	// daca nu este selectat
	if( !selected )
	{
		// culoare normala
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,diffuse.Array());
	}
	else
	{
		// culoarea atunci cand obiectul este selectat
		glColor3f(SelectedColor.x, SelectedColor.y, SelectedColor.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(SelectedColor.x,SelectedColor.y,SelectedColor.z,1)).Array());
	}
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.4,0.4,0.4,1)).Array());

	// daca este wireframe
	if( Wireframe )
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	// daca nu este wireframe
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}

	// desenare quaduri care alcatuiesc cubul
	// pentru fetele fata, spate, sus, jos s-au folost triangle-fans centrate in centrul fetei



	// Back face
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0,0.0,-1.0);
	glVertex3f ( 0, 0, -width/2); //fan center

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f( length/2,  height/2, -width/2);

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f( -length/2, height/2, -width/2);

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f(-length/2, -height/2, -width/2);

	glNormal3f(0.0,0.0,-1.0);
	glVertex3f(length/2,  -height/2, -width/2);
		
	glNormal3f(0.0,0.0,-1.0);
	glVertex3f( length/2,  height/2, -width/2);


	glEnd();


	// Front face
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0,0.0,1.0);
	glVertex3f ( 0, 0, +width/2); //fan center

	glNormal3f(0.0,0.0,1.0);
	glVertex3f( length/2,  height/2, width/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f( -length/2, height/2, width/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f(-length/2, -height/2, width/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f(length/2,  -height/2, width/2);

	glNormal3f(0.0,0.0,1.0);
	glVertex3f( length/2,  height/2, width/2);

	glEnd();


	// left face
	glBegin(GL_QUADS);
	glNormal3f(-1.0,0.0,0.0);
	glVertex3f( -length/2,  height/2, -width/2);

	glNormal3f(-1.0,0.0,0.0);
	glVertex3f( -length/2, height/2, width/2);

	glNormal3f(-1.0,0.0,0.0);
	glVertex3f(-length/2, -height/2, width/2);

	glNormal3f(-1.0,0.0,0.0);
	glVertex3f(-length/2,  -height/2, -width/2);

	glEnd();


	// right face
	glBegin(GL_QUADS);
	glNormal3f(1.0,0.0,0.0);
	glVertex3f( length/2,  height/2, -width/2);

	glNormal3f(1.0,0.0,0.0);
	glVertex3f( length/2, height/2, width/2);

	glNormal3f(1.0,0.0,0.0);
	glVertex3f(length/2, -height/2, width/2);

	glNormal3f(1.0,0.0,0.0);
	glVertex3f(length/2,  -height/2, -width/2);

	glEnd();

	// bottom face
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0,-1.0,0.0);
	glVertex3f ( 0, -height/2, 0); //fan center

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f( length/2,  -height/2, -width/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f( -length/2, -height/2, -width/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f(-length/2, -height/2, width/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f(length/2,  -height/2, width/2);

	glNormal3f(0.0,-1.0,0.0);
	glVertex3f( length/2,  -height/2, -width/2);
	
	glEnd();


	// top face
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0,1.0,0.0);	
	glVertex3f ( 0, height/2, 0); //fan center
	
	glNormal3f(0.0,1.0,0.0);
	glVertex3f( length/2,  height/2, -width/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f( -length/2, height/2, -width/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f(-length/2, height/2, width/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f(length/2,  height/2, width/2);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f( length/2,  height/2, -width/2);

	glEnd();

	glPopMatrix();
}
