#pragma once
#include "object3d.h"
#include "Light.h"
#include <stdio.h>

class LightPole : public Object3D
{
// VARIABILE
//-------------------------------------------------
private:
	// inaltimea
	float height;
	// stalpul
	Object3D pole;
	// capul luminii
	Object3D lightCup;
	//lumina de tip spot
	Light* light;

// FUNCTII
//-------------------------------------------------
public:
	//constructor ce primeste inaltimea stalpului
	LightPole(float height);

	// Draw - override fata de cea de la Object3D
	void Draw();


	//getters
	inline Light* getLight() {return light; }

	//setters
	void SetPosition(Vector3D *);
	void SetScale(Vector3D *);
	void SetColor(Vector3D *);
	void setDiffuseColor(Vector4D _diffuse);
	void setLightDirection(Vector3D);

	
	//destructor
	~LightPole(void);
};
