#pragma once
#include "object3d.h"
#include "Parallelepiped.h"
#include "Light.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#define MAX_COMPONENTS_NUMBER 16

#define ROTATION_ANGLE 0.05
#define FORWARD_SPEED 0.3

//Tipul de mutare al masinii
enum MovementType
{
	CAR_FORWARD,
	CAR_BACKWARD,
	CAR_LEFT,
	CAR_RIGHT
};

// derivat din Object3D
class Car :	public Object3D
{
// VARIABILE
//-------------------------------------------------
private:
	// Componentele masinii
	Parallelepiped *floor;
	Parallelepiped *roof;
	Parallelepiped *sideLeft;
	Parallelepiped *sideRight;
	Parallelepiped *front;
	Parallelepiped *back;
	Parallelepiped *frontHood;
	Parallelepiped *backHood;
	Parallelepiped *frontWindow;
	Parallelepiped *backWindow;
	Parallelepiped *leftWindow;
	Parallelepiped *rightWindow;
	Object3D *frontLeftWheel;
	Object3D *frontRightWheel;
	Object3D *backLeftWheel;
	Object3D *backRightWheel;
public:
	Light* frontLeftLight;
	Light* frontRightLight;
	Light* backLeftLight;
	Light* backRightLight;
private:
	//Toate componentele
	Object3D **components;
	int componentsNumber;
public:
	//Vectori folositi pentru deplasare/rotire
	Vector3D forwardVector;
	Vector3D rightVector;
	//lungimea masinii
	float length;
	//latimea masinii
	float width;
	//inaltimea masinii
	float height;

public:
	//celelalte obiecte, cu care se verifica ciocnirea
	Object3D **otherObjects;
	int otherObjectsCount;
	
// FUNCTII
//-------------------------------------------------
public:
	//Constructor fara parametrii
	Car(void);

	// Draw - override fata de cea de la Object3D
	void Draw();

	//setters
	void SetColor(Vector3D *);
	void setDiffuseColor(Vector4D);

	//Rotire stanga/dreapta - > unghi in radiani
	void rotateLeftRight(float angle);
	
	//Activare a luminilor
	void RenderLights();

	//mutarea masinii. Intoarce 1 daca masina a fost mutata, si 0 altfel
	int move(MovementType type);

	//Override functie scalare
	void SetScale(Vector3D *_scale);

	~Car(void);
};
