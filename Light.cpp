// EGC
// Laborator 5
//-------------------------------------------------

#include "Light.h"

// id-ul de baza
int Light::baseId = 0;

// constructor fara parametri, mosteneste constructorul de Sfera din Object3D
// deoarece dorim ca lumina sa fie ilustrata printr-o sfera
Light::Light() : Object3D(Sphere)
{
	// valori default
	diffuseLight = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.2,0.2,0.2);

	active=true;

	//atenuari default
	constantAttenuation=1;
	linearAttenuation=0.1;
	quadricAttenuation=0;

	// id-ul este unic, id-ul de baza incrementat
	id = baseId++;
	
	// sfera plasata in locul luminii nu este wireframe
	Wireframe = false;

	this->LightType=Ideal;
}

// constructor cu parametri, mosteneste constructorul de Sfera din Object3D
// deoarece dorim ca lumina sa fie ilustrata printr-o sfera
Light::Light(IlluminationType type) : Object3D(Sphere)
{
	// valori default
	diffuseLight = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.1,0.1,0.1);
	active=true;

	//atenuari default
	constantAttenuation=1;
	linearAttenuation=0.1;
	quadricAttenuation=0;
	
	//pentru lumina de tip spot
	direction= Vector3D(0,-1,0);
	cutoff=20;
	exponent=15;
	


	// id-ul este unic, id-ul de baza incrementat
	id = baseId++;
	
	// sfera plasata in locul luminii nu este wireframe
	Wireframe = false;

	//Setam tipul de lumina
	LightType=type;
}


// functie care plaseaza efectivl umina in scena
void Light::Render()
{
	if(this->active==false)
		return;

	// atenuari standard
	glLightf(GL_LIGHT0 + id,GL_CONSTANT_ATTENUATION,constantAttenuation);
	glLightf(GL_LIGHT0 + id,GL_LINEAR_ATTENUATION,linearAttenuation);
	glLightf(GL_LIGHT0 + id,GL_QUADRATIC_ATTENUATION,quadricAttenuation);

	// culoarea luminii 
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, diffuseLight.Array());
	// culoarea ambientala 
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient.Array());
	// culoarea speculara
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular.Array());
	// pozitia luminii
	glLightfv(GL_LIGHT0 + id, GL_POSITION, Vector4D(translation.x,translation.y,translation.z,1).Array());


	// daca lumina e de tip spot
	if(LightType==Spot)
	{
		glLightfv(GL_LIGHT0+id, GL_SPOT_DIRECTION, direction.Array());
		glLightf(GL_LIGHT0+id, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT0+id, GL_SPOT_EXPONENT, exponent);
	}

	// activam lumina
	glEnable(GL_LIGHT0 + id);
}

// functie care dezactiveaza lumina
void Light::Disable()
{
	glDisable(GL_LIGHT0 + id);
}

float Light::intensityInPoint(Vector3D point)
{
	float d=point.Distance(this->GetPosition());

	return 1/(constantAttenuation+linearAttenuation*d+quadricAttenuation*d*d);

}

void Light::resetLights()
{
	baseId=0;
}
