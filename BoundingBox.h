#pragma once

#include "Vector3D.h"

/*
	Axis-Aligned Bounding Box 
	Clasa ce contine coordonatele pentru bounding box-ul unui obiect.
	Coordonatele trebuie modificate din exterior
*/
class BoundingBox
{
// VARIABILE
//-------------------------------------------------
public:
	float maxX;
	float maxY;
	float maxZ;
	float minX;
	float minY;
	float minZ;

	Vector3D *position;

// METODE
//-------------------------------------------------
public:
	BoundingBox(Vector3D *_position);
	~BoundingBox(void);

	//Verifica existenta unei coliziuni cu un alt bounding box
	bool isCollision(BoundingBox* _otherBB);
};
