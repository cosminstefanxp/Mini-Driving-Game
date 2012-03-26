#pragma once
#include "object3d.h"

// derivat din Object3D
class Parallelepiped :	public Object3D
{

// VARIABILE
//-------------------------------------------------
private:
	// dimensiunile laturilor
	float length;
	float height;
	float width;



// FUNCTII
//-------------------------------------------------
public:
	// constructor fara parametri ce creaza un paralelipiped cu toate laturile 1
	Parallelepiped(void);
	// constructor care ia dimensiunile laturilor
	Parallelepiped(float length, float height, float  width);

	// Draw - override fata de cea de la Object3D
	void Draw();

	// Getteri
	inline float getLength() {return length; }
	inline float getHeight() {return height; }
	inline float getWidth() {return width; }

	// Setteri
	inline void setLength(float _length) { length=_length; }
	inline void setHeight(float _height) { height=_height; }
	inline void setWidth (float _width)  { width=_width; }



	
	// destructor
	~Parallelepiped(void);



};
