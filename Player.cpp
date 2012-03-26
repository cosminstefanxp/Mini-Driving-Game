#include "Player.h"

Player::Player()
{
	car=new Car();
	car->SetPosition(new Vector3D(0,0.25,-18));
	//car->SetRotation(new Vector3D(0,90,0));
	car->SetScale(new Vector3D(0.4,0.4,0.4));
	car->SetColor(new Vector3D(0,0.8,0));
	car->setDiffuseColor(Vector4D(0,0.3,0,1));

}

Player::~Player(void)
{
}

void Player::move(MovementType type)
{
	this->car->move(type);
	if(this->cameraType!=PCTFreeCam)
		this->repositionCamera();
}

void Player::repositionCamera()
{
	Vector3D position=car->GetPosition();
	//FreeCam - deja pozitionata, oriunde ar fi
	if(this->cameraType==PCTFreeCam)
	{
		camera->type=CameraTypeFREECAM;
		//Setam vectorii forward/up
		this->camera->SetForwardVector(this->car->forwardVector+Vector3D(0,-0.5,0));
		this->camera->SetUpVector(Vector3D(0,1,0));
		return ;
	}
	
	//OverHead - pozitionam camera
	if(this->cameraType==PCTOverhead)
	{
		this->camera->type=CameraTypeFIXED;

		//Setam pozitia ca fiind in spatele masinii
		position=position - this->car->forwardVector*6+Vector3D(0,5,0);
		this->camera->SetPosition(position);	
		//ReSetam vectorii up/right/forward
		this->camera->SetForwardVector(this->car->forwardVector+Vector3D(0,-0.5,0));
		this->camera->SetUpVector(Vector3D(0,1,0));
		this->camera->SetRightVector(this->camera->GetForwardVector().CrossProduct(this->camera->GetUpVector()));
	}

	//Nose - pozitionam camera
	if(this->cameraType==PCTNose)
	{
		this->camera->type=CameraTypeFIXED;

		//Setam pozitia ca fiind in fata masinii
		position=position + this->car->forwardVector*(this->car->length/2);
		this->camera->SetPosition(position);	
		//Setam vectorul forward
		this->camera->SetForwardVector(this->car->forwardVector);
		this->camera->SetUpVector(Vector3D(0,1,0));
	}

	//Satellite - pozitionam camera
	if(this->cameraType==PCTSatellite)
	{
		this->camera->type=CameraTypeFIXED;

		//Setam pozitia ca fiind in deasupra masinii
		position=position + Vector3D(0,25,0);
		this->camera->SetPosition(position);	
		//Setam vectorul up/forward
		this->camera->SetForwardVector(Vector3D(0,-1,0));
		this->camera->SetUpVector(this->car->forwardVector);
	}

}