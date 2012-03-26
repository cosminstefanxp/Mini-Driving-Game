// EGC
// Laborator 6
//-------------------------------------------------

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glut.h>
#include "BoundingBox.h"
#include "Vector3D.h"
#include "Vector4D.h"

// nivelul maxim de detaliu
#define MAXIMUM_LOD 50 

enum ObjectType
{
	Cube,			// glut cube
	Sphere,			// glut sphere
	Dodecahedron,	// glut dodecahedron
	Teapot,			// glut teapot
	Cone,			// glut cone
	Tetrahedron,		// glut tetrahedron	
	Custom,			// obiect propriu
	Cylinder,		// glu cylinder
	Torus			// glut torus
};
/*
	OBJECT3D
	Clasa pentru desenare si modificare a unui obiect 3d.
*/
class Object3D
{
// VARIABILE STATICE ::
//-------------------------------------------------
public:
	static Vector3D SelectedColor;
	static Vector3D ColorIncrement;

// VARIABILE
//-------------------------------------------------
// publice
public :
	// incep cu litera mare
	ObjectType Type;	// tipul obiectuliu
	bool Wireframe;		// daca va fi desenat wireframe
	bool Visible;		// daca va fi sau nu desenat
	bool Lighted;		// daca este sau nu luminat
	bool CollisionEnabled;	//daca se efectueaza calcule de ciocniri pentru acest obiect

// private
protected:
	// incep cu litera mica
	Vector3D translation;	// pozitie
public:
	Vector3D rotation;		// rotatie
protected:
	Vector3D scale;			// scalare
	Vector3D color;			// culoare
	Vector4D diffuse;		// culoare difuza ( atentie , la testul alfa se foloseste componenta A din culoarea difuza !!!_

	float levelOfDetail;	// nivelul de detaliu (pentru glutSphere)
	bool selected;			// daca este sau nu selectat

	GLUquadric *cylinderQuadric;

	//Clasa ce contine datele ce vor fi folosite pentru verificarea coliziunilor. 
	//Valorile continute (minx, miny, minz, etc) trebuie modificate din exterior).
	//TODO:
	//SetPosition si SetScale modifica automat valorile, dar SetRotation ar trebui rescris in restul obiectelor sau in Object3D
	BoundingBox *boundingBox;



// FUNCTII ::
//-------------------------------------------------
public:
// constructor
	// fara parametri
	Object3D();		
	// doar cu tip
	Object3D(ObjectType);
	// doar cu pozitie
	Object3D(Vector3D *);			
	// cu pozitie, rotatie, scalare
	Object3D(Vector3D *,Vector3D *,Vector3D *);

// functie de desenare
	void virtual Draw();

// setters 
	// pentru toate variabilele care nu sunt publice
	void Select();
	void Deselect();
	virtual void SetPosition(Vector3D *);
	virtual void SetRotation(Vector3D *);
	virtual void SetScale(Vector3D *);
	virtual void SetColor(Vector3D *);
	void SetLevelOfDetail(float);
		// Seteaza culoare difuza ( atentie , la testul alfa se foloseste componenta A din culoarea difuza !!!_
	virtual void setDiffuseColor(Vector4D _diffuse) {this->diffuse=_diffuse; }
// getters
	// pentru toate variabilele care nu sunt publice, si pot fi modificate din exterior
	Vector3D GetRotation();
	Vector3D GetScale();
	Vector3D GetPosition();
	float GetLevelOfDetail();

	//Seteaza marginile pentru bounding box, fata de centrul masinii (this->getPosition); Axis-aligned bounding box
	void virtual setBoundingBoxMargin(float _maxX,float _maxY, float _maxZ, float _minX, float _minY, float _minZ);	


	//Verifica daca exista coliziune cu un alt Obiect
	bool isCollision(Object3D *otherObj);
protected:
	// functie proprie de desenare. se apeleaza doar daca tipul este Custom
	void virtual customDraw();
	// seteaza valorile default 
	void defaultSettings();


	
	
};

#endif
