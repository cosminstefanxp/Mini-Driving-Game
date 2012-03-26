#include "Car.h"

Car::Car(void)
{
	//Vectorii directie
	forwardVector=Vector3D(1,0,0);
	rightVector=Vector3D(0,0,1);

	//Alocam vectorul de componente
	components=new Object3D*[MAX_COMPONENTS_NUMBER];
	componentsNumber=0;

	floor=new Parallelepiped(5,0.1,2);
	floor->SetPosition(new Vector3D(0,0,0));
	components[componentsNumber++]=floor;

	roof=new Parallelepiped(2,0.1,2);
	roof->SetPosition(new Vector3D(0,2,0));
	components[componentsNumber++]=roof;

	sideLeft=new Parallelepiped(5,0.1,1);
	sideLeft->SetRotation(new Vector3D(90,0,0));
	sideLeft->SetPosition(new Vector3D(0,0.5,1));
	components[componentsNumber++]=sideLeft;
	
	sideRight=new Parallelepiped(5,0.1,1);
	sideRight->SetRotation(new Vector3D(90,0,0));
	sideRight->SetPosition(new Vector3D(0,0.5,-1));
	components[componentsNumber++]=sideRight;

	front=new Parallelepiped(2,0.1,1);
	front->SetRotation(new Vector3D(90,0,90));
	front->SetPosition(new Vector3D(-2.5,0.5,0));
	components[componentsNumber++]=front;

	back=new Parallelepiped(2,0.1,1);
	back->SetRotation(new Vector3D(90,0,90));
	back->SetPosition(new Vector3D(2.5,0.5,0));
	components[componentsNumber++]=back;

	frontHood=new Parallelepiped(1,0.1,2);
	frontHood->SetPosition(new Vector3D(2,1,0));
	components[componentsNumber++]=frontHood;

	backHood=new Parallelepiped(1.3,0.1,2);
	backHood->SetPosition(new Vector3D(-1.85,1,0));
	components[componentsNumber++]=backHood;

	frontLeftWheel=new Object3D(Torus);
	frontLeftWheel->SetScale(new Vector3D(0.35,0.35,0.35));
	frontLeftWheel->SetPosition(new Vector3D(-1.6,0,1));
	frontLeftWheel->SetColor(new Vector3D(0,0,0));
	frontLeftWheel->setDiffuseColor(Vector4D(0,0,0,1));

	backLeftWheel=new Object3D(Torus);
	backLeftWheel->SetScale(new Vector3D(0.35,0.35,0.35));
	backLeftWheel->SetPosition(new Vector3D(-1.6,0,-1));
	backLeftWheel->SetColor(new Vector3D(0,0,0));
	backLeftWheel->setDiffuseColor(Vector4D(0,0,0,1));

	frontRightWheel=new Object3D(Torus);
	frontRightWheel->SetScale(new Vector3D(0.35,0.35,0.35));
	frontRightWheel->SetPosition(new Vector3D(1.6,0,1));
	frontRightWheel->SetColor(new Vector3D(0,0,0));
	frontRightWheel->setDiffuseColor(Vector4D(0,0,0,1));


	backRightWheel=new Object3D(Torus);
	backRightWheel->SetScale(new Vector3D(0.35,0.35,0.35));
	backRightWheel->SetPosition(new Vector3D(1.6,0,-1));
	backRightWheel->SetColor(new Vector3D(0.5,0.5,0.8));
	backRightWheel->setDiffuseColor(Vector4D(0,0,0,1));

	frontWindow=new Parallelepiped(1.2,0.1,2);
	frontWindow->SetColor(new Vector3D(0.2,0.2,0.5));
	frontWindow->setDiffuseColor(Vector4D(0,0,0.3,0.8));
	frontWindow->SetPosition(new Vector3D(1.27,1.5,0));
	frontWindow->SetRotation(new Vector3D(0,0,-60));

	backWindow=new Parallelepiped(1.1,0.1,2);
	backWindow->SetColor(new Vector3D(0.2,0.2,0.5));
	backWindow->setDiffuseColor(Vector4D(0,0,0.3,0.8));
	backWindow->SetPosition(new Vector3D(-1.1,1.5,0));
	backWindow->SetRotation(new Vector3D(0,0,75));

	leftWindow=new Parallelepiped(2,0.1,1);
	leftWindow->SetColor(new Vector3D(0.2,0.2,0.5));
	leftWindow->setDiffuseColor(Vector4D(0,0,0.3,0.8));
	leftWindow->SetRotation(new Vector3D(86,0,0));
	leftWindow->SetPosition(new Vector3D(0,1.5,1));

	rightWindow=new Parallelepiped(2,0.1,1);
	rightWindow->SetColor(new Vector3D(0.2,0.2,0.5));
	rightWindow->setDiffuseColor(Vector4D(0,0,0.3,0.8));
	rightWindow->SetRotation(new Vector3D(94,0,0));
	rightWindow->SetPosition(new Vector3D(0,1.5,-1));

	frontLeftLight=new Light(Spot);
	frontLeftLight->SetPosition(new Vector3D(2.52,0.8,0.8));
	frontLeftLight->SetColor(new Vector3D(1,1,1));
	frontLeftLight->setDiffuseColor(Vector4D(1,1,1,1));
	frontLeftLight->setDirection(Vector3D(1,-0.2,0));

	frontRightLight=new Light(Spot);
	frontRightLight->SetPosition(new Vector3D(2.52,0.8,-0.8));
	frontRightLight->SetColor(new Vector3D(1,1,1));
	frontRightLight->setDiffuseColor(Vector4D(1,1,1,1));
	frontRightLight->setDirection(Vector3D(1,-0.2,0));

	backLeftLight=new Light(Spot);
	backLeftLight->SetPosition(new Vector3D(-2.52,0.8,0.8));
	backLeftLight->SetColor(new Vector3D(1,0,0));
	backLeftLight->setDiffuseColor(Vector4D(1,0,0,1));
	backLeftLight->setDirection(Vector3D(-1,-0.4,0));

	backRightLight=new Light(Spot);
	backRightLight->SetPosition(new Vector3D(-2.52,0.8,-0.8));
	backRightLight->SetColor(new Vector3D(1,0,0));
	backRightLight->setDiffuseColor(Vector4D(1,0,0,1));
	backRightLight->setDirection(Vector3D(-1,-0.4,0));

	//Setare dimensiuni
	length=5;
	width=2;
	height=2; //e si cu 2 sub podea
	this->setBoundingBoxMargin(length/2,height,width/2,-length/2,0,width/2);
}

Car::~Car(void)
{
}

void Car::Draw()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
		return ;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	//Desenarea componentelor
	for(int i=0;i<componentsNumber;i++)
		components[i]->Draw();

	//Desenare roti
	frontLeftWheel->Draw();
	frontRightWheel->Draw();
	backLeftWheel->Draw();
	backRightWheel->Draw();

	//Desenare geamuri
	frontWindow->Draw();
	backWindow->Draw();
	leftWindow->Draw();
	rightWindow->Draw();

	//Desenare lumini
	frontLeftLight->Draw();
	frontRightLight->Draw();
	backLeftLight->Draw();
	backRightLight->Draw();

	glPopMatrix();
}

void Car::SetColor(Vector3D *_value)
{
	for(int i=0;i<componentsNumber;i++)
		components[i]->SetColor(_value);
}

void Car::setDiffuseColor(Vector4D _value)
{
	for(int i=0;i<componentsNumber;i++)
		components[i]->setDiffuseColor(_value);
}

void Car::rotateLeftRight(float angle)
{
	//Rotirea masinii
	float unghiGrade=angle*180.0f/M_PI;
	this->SetRotation(&(this->GetRotation()-Vector3D(0,unghiGrade,0))); //minus sa fie sens ceasornic

	//Rotirea vectorilor directie
	Vector3D FwdNew = forwardVector * cos(angle) + rightVector * sin(angle);
	Vector3D RightNew = rightVector * cos(angle) - forwardVector * sin(angle);

	forwardVector=FwdNew;
	rightVector=RightNew;

	//Reactualizare bounding box - se pot modifica doar maxX/maxZ, minX/minZ
	Vector3D colt;
	float minX=99999;
	float minZ=99999;
	float maxX=-99999;
	float maxZ=-99999;

	//Colt fata dreapta
	colt=forwardVector*(length/2) + rightVector*(width/2);
	if(colt.x>maxX)
		maxX=colt.x;
	if(colt.x<minX)
		minX=colt.x;
	if(colt.z>maxZ)
		maxZ=colt.z;
	if(colt.z<minZ)
		minZ=colt.z;
	//Colt fata stanga
	colt=forwardVector*(length/2) - rightVector*(width/2);
	if(colt.x>maxX)
		maxX=colt.x;
	if(colt.x<minX)
		minX=colt.x;
	if(colt.z>maxZ)
		maxZ=colt.z;
	if(colt.z<minZ)
		minZ=colt.z;
	//Colt spate dreapta
	colt=-forwardVector*(length/2) + rightVector*(width/2);
	if(colt.x>maxX)
		maxX=colt.x;
	if(colt.x<minX)
		minX=colt.x;
	if(colt.z>maxZ)
		maxZ=colt.z;
	if(colt.z<minZ)
		minZ=colt.z;
	//Colt spate stanga
	colt=-forwardVector*(length/2) - rightVector*(width/2);
	if(colt.x>maxX)
		maxX=colt.x;
	if(colt.x<minX)
		minX=colt.x;
	if(colt.z>maxZ)
		maxZ=colt.z;
	if(colt.z<minZ)
		minZ=colt.z;


	this->setBoundingBoxMargin(maxX,this->boundingBox->maxY,maxZ,minX,this->boundingBox->minY,minZ);
	printf("New Car bounding Box coordinates: (%f,%f,%f) - (%f,%f,%f)\n",maxX,this->boundingBox->maxY,maxZ,minX,this->boundingBox->minY,minZ);
}

void Car::RenderLights()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
		return ;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// Render al luminilor
	this->frontLeftLight->Render();
	this->frontRightLight->Render();
	this->backLeftLight->Render();
	this->backRightLight->Render();


	glPopMatrix();
}

int Car::move(MovementType type)
{
	//Doing the move
	switch(type)
	{
	case CAR_FORWARD: this->SetPosition(&(this->GetPosition()+forwardVector*FORWARD_SPEED)); break;
	case CAR_BACKWARD: this->SetPosition(&(this->GetPosition()-forwardVector*FORWARD_SPEED)); break;
	case CAR_LEFT: this->rotateLeftRight(-ROTATION_ANGLE); break;
	case CAR_RIGHT: this->rotateLeftRight(+ROTATION_ANGLE); break;
	}

	//Checking for collisions
	bool haveToUndo=false;
	for(int i=0;i<otherObjectsCount;i++)
		if(this!=otherObjects[i] && this->isCollision(otherObjects[i]))
		{
			printf("Collision detected with object %d, Undoing move!\n",i);
			haveToUndo=true;
			break;
		}

	//Reversing the move, if needed
	if(haveToUndo)
	{

		switch(type)
		{
		case CAR_BACKWARD: this->SetPosition(&(this->GetPosition()+forwardVector*FORWARD_SPEED)); break;
		case CAR_FORWARD: this->SetPosition(&(this->GetPosition()-forwardVector*FORWARD_SPEED)); break;
		case CAR_RIGHT: this->rotateLeftRight(-ROTATION_ANGLE); break;
		case CAR_LEFT: this->rotateLeftRight(+ROTATION_ANGLE); break;
		}
		return 0; //masina nu a fost mutata
	}
	//masina a fost mutata
	return 1;
}

void Car::SetScale(Vector3D *_scale)
{
	this->length *=_scale->x;
	this->height *=_scale->y;
	this->width  *=_scale->z;

	Object3D::SetScale(_scale);
}