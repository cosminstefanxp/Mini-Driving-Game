// EGC
// Laborator 5
//-------------------------------------------------

#ifndef LIGHT_H
#define LIGHT_H

#include <glut.h>
#include "Object3D.h"

// tipul de iluminare
enum IlluminationType
{
	Ideal, // lumina omnidirectionala
	Spot   // lumina directionala
};

/*
	Light
	Clasa pentru desenarea si activarea unei lumini.
*/

// derivata din object3D
class Light : public Object3D
{

// VARIABILE STATICE
//-------------------------------------------------
private:
	static int baseId;

// VARIABILE
//-------------------------------------------------
public:
	// tipul luminii - nu este folosit, inca
	IlluminationType LightType;

	//daca este activa sau nu
	bool active;

private:
	// id-ul asignat. pleaca din 0 si este folosit pentru GL_LIGHT0 + id
	int id;
	// lumina difuza
	Vector4D diffuseLight;
	// lumina ambientala
	Vector4D ambient;
	// lumina speculara
	Vector4D specular;
	
	//Pentru lumina spot:
	Vector3D direction;
	GLfloat cutoff;
	GLfloat exponent;
	
	//constantele de atenuare
	GLfloat constantAttenuation;
	GLfloat linearAttenuation;
	GLfloat quadricAttenuation;
	

// FUNCTII
//-------------------------------------------------
public:
	// constructor fara parametri
	Light();
	// constructor cu tip
	Light(IlluminationType);

	// plaseaza lumina in scena si o activeaza
	void Render();
	// dezactiveaza lumina
	void Disable();

	float intensityInPoint(Vector3D);

	static void resetLights();

	// SETTERS
	// seteaza atenuarile
	inline void setConstantAttenuation(GLfloat _attenuation)	{constantAttenuation=_attenuation;}
	inline void setLinearAttenuation(GLfloat _attenuation)		{linearAttenuation=_attenuation;}
	inline void setQuadricAttenuation(GLfloat _attenuation)		{quadricAttenuation=_attenuation;}

	// seteaza proprietatile spotului
	inline void setCutoff(GLfloat _cutoff)		{cutoff=_cutoff;}
	inline void setExponent(GLfloat _exponent)	{exponent=_exponent;}
	inline void setDirection(Vector3D _direct)	{direction=_direct;}

	//seteaza culorile luminii
	inline void setDiffuseLightColor(Vector4D _color)	{	diffuseLight=_color;}
	inline void setAmbientLightColor(Vector4D _color)	{	ambient=_color;}
	inline void setSpecularLightColor(Vector4D _color)	{	specular=_color;}

	//GETTERS
	//obtinem atenuarile
	inline GLfloat getConstantAttenuation() {return constantAttenuation; }
	inline GLfloat getLinearAttenuation()	{return linearAttenuation; }
	inline GLfloat getQuadricAttenuation()	{return quadricAttenuation; }

	// obtine proprietatile spotului
	inline GLfloat getCutoff()		{return cutoff;}
	inline GLfloat getExponent()	{return exponent;}
	inline Vector3D getDirection()	{return direction;}



};

#endif