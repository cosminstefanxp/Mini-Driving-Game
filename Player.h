#pragma once
#include "object3d.h"
#include "Car.h"
#include "Camera.h"
#include "Vector3D.h"

//tipurile de camera din joc
enum PlayerCameraType
{
	PCTOverhead,
	PCTNose,
	PCTSatellite,
	PCTFreeCam
};

class Player 
{
// VARIABILE
//-------------------------------------------------
	public:
		Car *car;
		Camera *camera;
		PlayerCameraType cameraType;

// METODE
//-------------------------------------------------
	public:
		Player(void);
		~Player(void);

		//Muta jucatorul
		void move(MovementType type);
		//Rearanjeaza camera, in functie de tipul sau
		void repositionCamera();
};
