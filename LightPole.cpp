#include "LightPole.h"


// derivat din Object3D
LightPole::LightPole(float _height) : Object3D(Custom)
{
	this->height=_height;
	this->pole=Object3D(Cylinder);
	this->lightCup=Object3D(Cone);

	this->pole.SetScale(new Vector3D(0.2,0.2,_height));
	this->pole.SetRotation(new Vector3D(-90,0,0));
	this->lightCup.SetPosition(new Vector3D(0,_height,0));
	this->lightCup.SetRotation(new Vector3D(-90,0,0));

	this->light=new Light(Spot);
	this->light->setDirection(Vector3D(0,-1,0));
	this->light->SetPosition(new Vector3D(0,_height,0));
	this->light->active=true;
	//printf("c:%p\n",this->light);
}

LightPole::~LightPole(void)
{
}

// Draw - override fata de cea de la Object3D
void LightPole::Draw()
{
	this->pole.Draw();
	this->lightCup.Draw();
}

void LightPole::SetColor(Vector3D *_color)
{
	Object3D::SetColor(_color);
	this->pole.SetColor(_color);
	this->lightCup.SetColor(_color);
}

void LightPole::SetPosition(Vector3D *_position)
{
	Object3D::SetPosition(_position);
	pole.SetPosition(_position);
	lightCup.SetPosition(&(*_position + Vector3D(0,height,0)));
	light->SetPosition(&(*_position + Vector3D(0,height,0)));
}

void LightPole::SetScale(Vector3D *_scale)
{
	Object3D::SetScale(_scale);
	Vector3D _scale_temp=Vector3D(_scale->x, _scale->z, _scale->y); //La cilindru, z e inaltimea
	pole.SetScale(&(pole.GetScale()*(_scale_temp)));
	lightCup.SetScale(&(lightCup.GetScale()*(*_scale)));
	height=height * _scale->y;
	lightCup.SetPosition(&(this->GetPosition() + Vector3D(0,height,0)));
	light->SetPosition(&(this->GetPosition() + Vector3D(0,height,0)));
}

void LightPole::setLightDirection(Vector3D _direction)
{
	this->light->setDirection(_direction);
}

void LightPole::setDiffuseColor(Vector4D _diffuse)
{
	this->lightCup.setDiffuseColor(_diffuse);
	this->pole.setDiffuseColor(_diffuse);
}