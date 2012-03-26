#ifndef CUBE_H
#define CUBE_H

#include <glut.h>
#include "Object3D.h"
#include "Camera.h"

class Cube : public Object3D
{
public:

	// Construcot
	Cube();

	// Draw
	void Draw();

public:
	// Functie pentru a seta latura cubului
	void SetLatura(GLfloat latura);
	// Seteaza culoare difuza ( atentie , la testul alfa se foloseste componenta A din culoarea difuza !!!_
	void SetDiffuse(Vector4D *color);
	
private:
	// latura cubului
	GLfloat latura;
	// culoare difuza
	Vector4D diffuse;
	// culoare ambientala
	Vector4D ambient;
	// culoare speculara
	Vector4D specular;
};


#endif
