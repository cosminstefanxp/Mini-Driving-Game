//-------------------------------------------------
// EGC
// Tema 4: Need for Speed
//-------------------------------------------------
// Stefan-Dobrin Cosmin
// 331CA
//-------------------------------------------------


#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <stdarg.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>

#include "Parallelepiped.h"
#include "Car.h"
#include "LightPole.h"
#include "Player.h"
#include "Camera.h"
#include "Object3D.h"
#include "Plane.h"
#include "Light.h"
#include "Vector3D.h"
#include "Vector4D.h"

#define SIDEWINDOW_HEIGHT 200
#define SIDEWINDOW_WIDTH 250
#define SIDE_HEIGHT 0.6
#define SIDE_WIDTH 0.3
#define INNER_CORNER_BB_REDUCTION 0.6

// Animatii obiecte
// Variabila ce reprezinta indicele, in vectorul objects, al obiectului ce se roteste
int rotatingObject;
int translatingObject;
int translationTimer=10;
float translationSpeed=0.05;


// tasta escape
#define ESC	27

float *Vector3D::arr;
float *Vector4D::arr;

// VARIABILE
//-------------------------------------------------

// Optiuni de camera/vizualizare
bool fullscreen=false;
// camera
Camera *camera;
// camera mica
Camera *cameraSide;
// fereastra
int mainWindow=-1, sideWindow=-1;
//contor pentru update in fereastra secundara
int sideCounter=0;

//Tipuri de camera
PlayerCameraType cameraType[]={PCTFreeCam,PCTSatellite,PCTNose,PCTOverhead};
int currentCamera=0;
int cameraTypeNumber=4;

//Mouse
// Statusul fiecarui buton. 
int buttons[5] = {GLUT_UP, GLUT_UP, GLUT_UP, GLUT_UP, GLUT_UP}; 
//Coordonatele ultimului click/actiune a mouseului
int mouseXClick, mouseYClick;

//Keyboard
bool upKeyPressed=false;
bool downKeyPressed=false;
bool leftKeyPressed=false;
bool rightKeyPressed=false;

// numarul de obiecte
int objectCount;
// vector de obiecte 3D
Object3D **objects;

// numarul de obiecte cu care trebuie verificate coliziunile
int collidableObjectCount;
Object3D **collidableObjects;

// Jucatorul
Player *player;

// planul de baza
Plane *ground;

//Lumini
int lightCount;
Light **lights;



// FUNCTII
//-------------------------------------------------

//creaza circuitul 
void createTrack()
{
	Vector4D sideDiffuseColor(0,0,0.3,1);
	Vector3D *sideColor=new Vector3D(0,0,1);	//un singur vector pentru ca toate marginile au aceeasi culoare -> e suficienta o singura referinta

	Parallelepiped *groundSide;
	//stanga exterior
	groundSide=new Parallelepiped(40,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(-20,SIDE_HEIGHT/2,0));
	groundSide->SetRotation(new Vector3D(0,90,0));
	groundSide->setBoundingBoxMargin(SIDE_WIDTH/2,SIDE_HEIGHT/2,20,-SIDE_WIDTH/2,-SIDE_HEIGHT/2,-20);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//sus1 exterior
	groundSide=new Parallelepiped(30,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(-5,SIDE_HEIGHT/2,-20));
	//groundSide->SetRotation(new Vector3D(0,90,0)); //0 rotatie
	groundSide->setBoundingBoxMargin(15,SIDE_HEIGHT/2,SIDE_WIDTH/2,-15,-SIDE_HEIGHT/2,-SIDE_WIDTH/2);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//dreapta1 exterior
	groundSide=new Parallelepiped(12,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(10,SIDE_HEIGHT/2,-14));
	groundSide->SetRotation(new Vector3D(0,90,0));
	groundSide->setBoundingBoxMargin(SIDE_WIDTH/2,SIDE_HEIGHT/2,6,-SIDE_WIDTH/2,-SIDE_HEIGHT/2,-6);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;


	//sus2 exterior
	groundSide=new Parallelepiped(10,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(15,SIDE_HEIGHT/2,-8));
	//groundSide->SetRotation(new Vector3D(0,90,0)); //0 rotatie
	groundSide->setBoundingBoxMargin(5,SIDE_HEIGHT/2,SIDE_WIDTH/2,-5,-SIDE_HEIGHT/2,-SIDE_WIDTH/2);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//dreapta2 exterior
	groundSide=new Parallelepiped(28,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(20,SIDE_HEIGHT/2,6));
	groundSide->SetRotation(new Vector3D(0,90,0));
	groundSide->setBoundingBoxMargin(SIDE_WIDTH/2,SIDE_HEIGHT/2,14,-SIDE_WIDTH/2,-SIDE_HEIGHT/2,-14);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//jos exterior
	groundSide=new Parallelepiped(40,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(0,SIDE_HEIGHT/2,20));
	//groundSide->SetRotation(new Vector3D(0,90,0)); //0 rotatie
	groundSide->setBoundingBoxMargin(20,SIDE_HEIGHT/2,SIDE_WIDTH/2,-20,-SIDE_HEIGHT/2,-SIDE_WIDTH/2);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;


	//stanga interior
	groundSide=new Parallelepiped(32,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(-16,SIDE_HEIGHT/2,0));
	groundSide->SetRotation(new Vector3D(0,90,0));
	groundSide->setBoundingBoxMargin(SIDE_WIDTH/2,SIDE_HEIGHT/2,16-INNER_CORNER_BB_REDUCTION,-SIDE_WIDTH/2,-SIDE_HEIGHT/2,-16+INNER_CORNER_BB_REDUCTION);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//sus1 interior
	groundSide=new Parallelepiped(22,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(-5,SIDE_HEIGHT/2,-16));
	//groundSide->SetRotation(new Vector3D(0,90,0)); //0 rotatie
	groundSide->setBoundingBoxMargin(11-INNER_CORNER_BB_REDUCTION,SIDE_HEIGHT/2,SIDE_WIDTH/2,-11+INNER_CORNER_BB_REDUCTION,-SIDE_HEIGHT/2,-SIDE_WIDTH/2);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//dreapta1 interior
	groundSide=new Parallelepiped(12,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(6,SIDE_HEIGHT/2,-10));
	groundSide->SetRotation(new Vector3D(0,90,0));
	groundSide->setBoundingBoxMargin(SIDE_WIDTH/2,SIDE_HEIGHT/2,6-INNER_CORNER_BB_REDUCTION,-SIDE_WIDTH/2,-SIDE_HEIGHT/2,-6+INNER_CORNER_BB_REDUCTION);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//sus2 interior
	groundSide=new Parallelepiped(10,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(11,SIDE_HEIGHT/2,-4));
	//groundSide->SetRotation(new Vector3D(0,90,0)); //0 rotatie
	groundSide->setBoundingBoxMargin(5-INNER_CORNER_BB_REDUCTION,SIDE_HEIGHT/2,SIDE_WIDTH/2,-5+INNER_CORNER_BB_REDUCTION,-SIDE_HEIGHT/2,-SIDE_WIDTH/2);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//dreapta2 interior
	groundSide=new Parallelepiped(20,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(16,SIDE_HEIGHT/2,6));
	groundSide->SetRotation(new Vector3D(0,90,0));
	groundSide->setBoundingBoxMargin(SIDE_WIDTH/2,SIDE_HEIGHT/2,10-INNER_CORNER_BB_REDUCTION,-SIDE_WIDTH/2,-SIDE_HEIGHT/2,-10+INNER_CORNER_BB_REDUCTION);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

	//jos interior
	groundSide=new Parallelepiped(32,SIDE_HEIGHT,SIDE_WIDTH);
	groundSide->SetColor(sideColor);
	groundSide->setDiffuseColor(sideDiffuseColor);
	groundSide->SetPosition(new Vector3D(0,SIDE_HEIGHT/2,16));
	//groundSide->SetRotation(new Vector3D(0,90,0)); //0 rotatie
	groundSide->setBoundingBoxMargin(16-INNER_CORNER_BB_REDUCTION,SIDE_HEIGHT/2,SIDE_WIDTH/2,-16+INNER_CORNER_BB_REDUCTION,-SIDE_HEIGHT/2,-SIDE_WIDTH/2);
	collidableObjects[collidableObjectCount++] = groundSide;
	objects[objectCount++] = groundSide;

}


// functie de initializare
void init(void)
{
	// initialize vector arrays
	Vector3D::arr = new float[3];
	Vector4D::arr = new float[4];

	// initializam camera principala
	camera = new Camera();
	camera->type=CameraTypeFREECAM;
	camera->SetPosition(Vector3D(0,10,20));

	//initializam camera secundara
	cameraSide = new Camera();
	cameraSide->SetPosition(Vector3D(0,40,33));
	cameraSide->RotateX(0.94);
	cameraSide->type=CameraTypeFIXED;

	//numarul de obiecte
	objectCount = 35;
	// initializam vectorii de obiecte
	objects = new Object3D*[objectCount];
	collidableObjects = new Object3D*[objectCount];
	lights = new Light*[objectCount];
	
	//Pentru numararea obiectelor
	objectCount=0;
	lightCount=0;
	collidableObjectCount=0;

	/***********PLANUL DE JOC****************/
	// initializam un plan de latura 5.0f
	ground = new Plane(20.4f);
	// culoare
	ground->SetColor(new Vector3D(0.8,0,0.0));
	// setam o grila de 5
	ground->SetLevelOfDetail(2);
	// sub nivelul obiectelor
	ground->SetPosition(new Vector3D(0,0,0));
	// si wireframe
	ground->Wireframe = false;

	/********MARGINILE TERENULUI DE JOC********/
	//Cream marginile terenului jocului
	createTrack();

	/*********STALPI DE LUMINA****************/
	LightPole *lightPole;
	//Stalp 1
	lightPole=new LightPole(10);
	lightPole->SetColor(new Vector3D(0.4,0.4,0));
	lightPole->setDiffuseColor(Vector4D(0.4,0.4,0,1));
	lightPole->SetScale(new Vector3D(0.5,0.5,0.5));
	lightPole->setLightDirection(Vector3D(-0.5,-1,0));
	lightPole->SetPosition(new Vector3D(-16,0,0));
	lightPole->setBoundingBoxMargin(0.01,6,0.01,-0.01,-6,-0.01);
	lightPole->CollisionEnabled=false;
	objects[objectCount++]=lightPole;
	lights[lightCount++]=lightPole->getLight();
	
	//Stalp 2
	lightPole=new LightPole(6);
	lightPole->SetColor(new Vector3D(0.4,0.7,0));
	lightPole->setDiffuseColor(Vector4D(0.4,0.7,0,1));
	lightPole->SetScale(new Vector3D(0.5,0.5,0.5));
	lightPole->setLightDirection(Vector3D(-0.5,-1,0.5));
	lightPole->SetPosition(new Vector3D(10,0,-8));
	lightPole->setBoundingBoxMargin(0.01,6,0.01,-0.01,-6,-0.01);
	lightPole->CollisionEnabled=false;
	objects[objectCount++]=lightPole;
	lights[lightCount++]=lightPole->getLight();

	//Stalp 3
	lightPole=new LightPole(12);
	lightPole->SetColor(new Vector3D(0,0.4,0.4));
	lightPole->setDiffuseColor(Vector4D(0,0.4,0.4,1));
	lightPole->SetScale(new Vector3D(0.5,0.5,0.5));
	lightPole->setLightDirection(Vector3D(0.5,-1.3,0.3));
	lightPole->SetPosition(new Vector3D(16,0,16));
	lightPole->setBoundingBoxMargin(0.01,6,0.01,-0.01,-6,-0.01);
	lightPole->CollisionEnabled=false;
	objects[objectCount++]=lightPole;
	lights[lightCount++]=lightPole->getLight();

	/*************OBSTACOLE*************/
	Object3D *obstacol;

	//Obstacol 1 - Sfera portocalie - sus 
	obstacol=new Object3D(Sphere);
	obstacol->setDiffuseColor(Vector4D(0.5,0.2,0,1));
	obstacol->SetColor(new Vector3D(0.5,0.2,0));
	obstacol->SetScale(new Vector3D(0.5,0.5,0.5));
	obstacol->SetPosition(new Vector3D(-4,1,-19));
	obstacol->setBoundingBoxMargin(0.5,0.5,0.5,-0.5,-0.5,-0.5);
	objects[objectCount++]=obstacol;

	//Obstacol 2 - Paralelipiped mov - dreapta 
	obstacol=new Object3D(Cube);
	obstacol->setDiffuseColor(Vector4D(0.4,0.1,0.4,1));
	obstacol->SetColor(new Vector3D(0.4,0.1,0.4));
	obstacol->SetScale(new Vector3D(1,1.6,1));
	obstacol->SetPosition(new Vector3D(16.65,0.5,2));
	obstacol->setBoundingBoxMargin(0.5,0.8,0.5,-0.5,-0.8,-0.5);
	objects[objectCount++]=obstacol;

	//Obstacol 3 - Romb Turcuaz - jos 
	obstacol=new Object3D(Cube);
	obstacol->setDiffuseColor(Vector4D(0,0.6,0.4,1));
	obstacol->SetColor(new Vector3D(0,0.5,0.4));
	obstacol->SetScale(new Vector3D(1,1,1));
	obstacol->SetRotation(new Vector3D(45,45,0));
	obstacol->SetPosition(new Vector3D(12,1,17));
	obstacol->setBoundingBoxMargin(0.7,0.7,0.7,-0.7,-0.7,-0.7);
	rotatingObject=objectCount;
	objects[objectCount++]=obstacol;

	//Obstacol 4 - Cub galben - jos 
	obstacol=new Object3D(Cube);
	obstacol->setDiffuseColor(Vector4D(0.5,0.5,0,0.8));
	obstacol->SetColor(new Vector3D(0.5,0.5,0));
	obstacol->SetScale(new Vector3D(1,1.6,1));
	obstacol->SetPosition(new Vector3D(6,0.5,19));
	obstacol->setBoundingBoxMargin(0.5,0.5,0.5,-0.5,-0.5,-0.5);
	objects[objectCount++]=obstacol;

	//Obstacol 5 - Torus Verde - jos 
	obstacol=new Object3D(Torus);
	obstacol->setDiffuseColor(Vector4D(0,0.5,0,1));
	obstacol->SetColor(new Vector3D(0,0.5,0));
	obstacol->SetScale(new Vector3D(0.4,0.4,0.4));
	obstacol->SetPosition(new Vector3D(-10,0,19.5));
	obstacol->setBoundingBoxMargin(0.5,0.5,0.4,-0.5,-0.4,-0.5);
	objects[objectCount++]=obstacol;

	//Obstacol 6 - Sfera portocalie - jos 
	obstacol=new Object3D(Sphere);
	obstacol->setDiffuseColor(Vector4D(0.8,0.2,0,0.6));
	obstacol->SetColor(new Vector3D(0.5,0.2,0));
	obstacol->SetScale(new Vector3D(0.5,0.5,0.5));
	obstacol->SetPosition(new Vector3D(-5,1,16.8));
	obstacol->setBoundingBoxMargin(0.5,0.5,0.5,-0.5,-0.5,-0.5);
	translatingObject=objectCount;
	objects[objectCount++]=obstacol;

	//Obstacol 7 - Cilindru rosu - stanga 
	obstacol=new Object3D(Cylinder);
	obstacol->setDiffuseColor(Vector4D(0.8,0,0.1,0.6));
	obstacol->SetColor(new Vector3D(0.8,0,0.1));
	obstacol->SetScale(new Vector3D(0.3,0.3,4));
	obstacol->SetRotation(new Vector3D(90,0,0));
	obstacol->SetPosition(new Vector3D(-19.5,1,7));
	obstacol->setBoundingBoxMargin(0.3,4,0.3,-0.3,-4,-0.3);
	objects[objectCount++]=obstacol;

	//Obstacol 8 - Con albastru - stanga 
	obstacol=new Object3D(Cone);
	obstacol->setDiffuseColor(Vector4D(0,0,0.6,1));
	obstacol->SetColor(new Vector3D(0.8,0,0.1));
	obstacol->SetScale(new Vector3D(0.3,0.3,2));
	obstacol->SetRotation(new Vector3D(-90,0,0));
	obstacol->SetPosition(new Vector3D(-18.5,0,-10));
	obstacol->setBoundingBoxMargin(0.3,2,0.3,-0.3,0,-0.3);
	objects[objectCount++]=obstacol;
	
	

	/**************JUCATOR**************/
	player=new Player();
	objects[objectCount++]=player->car;
	player->car->otherObjects=objects;
	player->car->otherObjectsCount=objectCount;
	player->camera=camera;
	player->cameraType=PCTFreeCam;




	/*************LUMINI****************/

	//Lumina ambientala
	lights[lightCount++]=new Light();
	lights[lightCount-1]->setDiffuseColor(Vector4D(1,0,1,1));
	lights[lightCount-1]->SetPosition(new Vector3D(0,20,0));
	



	// pregatim o scena noua in opengl
	glClearColor(0.0, 0.0, 0.0, 0.0);	// stergem tot
	glEnable(GL_DEPTH_TEST);			// activam verificarea distantei fata de camera (a adancimii)
	glShadeModel(GL_SMOOTH);			// mod de desenare SMOOTH
	glEnable(GL_LIGHTING);				// activam iluminarea
	glEnable(GL_NORMALIZE);				// activam normalizarea normalelor
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,(Vector4D(1,1,1,1)).Array());
	glEnable(GL_ALPHA_TEST);
}

// functie pentru output text
void output(GLfloat x, GLfloat y, char *format,...)
{
	va_list args;

	char buffer[1024],*p;

	va_start(args,format);

	vsprintf_s(buffer, format, args);

	va_end(args);

	glPushMatrix();
	
	glTranslatef(x,y,24);

	glRotatef(-90,1,0,0);

	glScalef(0.02, 0.02, 0.0); /* 0.1 to 0.001 as required */


	for (p = buffer; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);

	glPopMatrix();
}

// functie de desenare a scenei 3D
void drawScene(void)
{
	// plasare observator
	if(glutGetWindow() == mainWindow)
	{
		camera->Render();
	}
	// plasare camera secundara
	if(glutGetWindow() == sideWindow)
	{
		cameraSide->Render();
	}

	//Afisare text
	if(glutGetWindow() == sideWindow)
	{
		glColor3f(1.0,1.0,1.0);

		glLineWidth(1.0);
		switch(player->cameraType)
		{
			case PCTFreeCam: output(-18,3,"Camera: FreeCam\n"); break;
			case PCTNose:	output(-18,3,"Camera: Nose\n"); break;
			case PCTOverhead: output(-18,3,"Camera: Overhead\n"); break;
			case PCTSatellite: output(-18,3,"Camera: Satellite\n"); break;
			default: output(-18,3,"Camera type: Unknown\n"); break;
		}
	}

	// activare lumini
	for(int i=0;i<lightCount;i++)
	{
		lights[i]->Render();
		//lights[i]->Draw();
	}

	player->car->RenderLights();


	// desenare plan
	ground->Draw();

	// desenare obiecte
	for ( int i = 0 ; i < objectCount ; i ++ )
		objects[i]->Draw();

	

	// dezactivare lumini
	for(int i=0;i<lightCount;i++)
	{
		lights[i]->Disable();
	}

	player->car->frontLeftLight->Disable();
	player->car->frontRightLight->Disable();


}

// functie de desenare (se apeleaza cat de repede poate placa video)
void display(void)
{
	// stergere ecran
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Render Pass - deseneaza scena
	glAlphaFunc(GL_GEQUAL, 1.0f);
	//Deseneaza scena
	drawScene();

	// Transparency Pass - deseneaza scena transparenta
	glAlphaFunc(GL_LESS, 1.0f);
	//glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
	drawScene();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	//glEnable(GL_CULL_FACE);

	// double buffering
	glutSwapBuffers();

	//// redeseneaza scena
	//if(glutGetWindow() == sideWindow)
	//{
	//	glutPostRedisplay();
	//}

}


// functie de update (se apeleaza constant, independent de Draw() )
void update(void)
{
	Sleep(20);
	sideCounter++;
	translationTimer++;

	//Actualizeaza masina jucatorului
	bool carMoved=false;
	if(rightKeyPressed)
		player->move(CAR_RIGHT),carMoved=true;
		
	if(leftKeyPressed)
		player->move(CAR_LEFT),carMoved=true; 

	if(downKeyPressed)
		player->move(CAR_BACKWARD),carMoved=true; 

	if(upKeyPressed)
		player->move(CAR_FORWARD),carMoved=true; 
	
	//Actualizeaza obiectele animate
	//Rotatia
	objects[rotatingObject]->SetRotation(&(objects[rotatingObject]->GetRotation()+Vector3D(0,10,0)));
	if(objects[rotatingObject]->rotation.y > 360)
		objects[rotatingObject]->rotation.y=0;
	//Translatia
	objects[translatingObject]->SetPosition(&(objects[translatingObject]->GetPosition()+Vector3D(0,translationSpeed,0)));
	if(translationTimer>20)
	{
		translationTimer=0;
		translationSpeed=-translationSpeed;
	}


	// redeseneaza scena
	glutPostWindowRedisplay(mainWindow);

	if(sideCounter==7)
	{
		if(sideWindow!=-1 && fullscreen==false)
		{
			glutPostWindowRedisplay(sideWindow);
		}
		sideCounter=0;
	}
}


// handler pentru tastatura
void keyboard(unsigned char key , int x, int y)
{
	switch (key)
	{
	// la escape se iese din program
	case ESC : exit(0);
	//	// cu < si > se modifica nivelul de detaliu al terenului
	//case ',' : ground->SetLevelOfDetail(ground->GetLevelOfDetail()*2); break;
	//case '.' : ground->SetLevelOfDetail(ground->GetLevelOfDetail()/2); break;
		// cu W A S D Q E observatorul se misca prin scena
	case 'w' : case 'W' : 
		camera->MoveForward(0.5); break;
	case 's' : case 'S' : 
		camera->MoveBackward(0.5); break;
	case 'a' : case 'A' : 
		camera->MoveLeft(0.5); break;
	case 'd' : case 'D' : 
		camera->MoveRight(0.5); break;
	case '8':
		camera->MoveUpward(0.1); break;
	case '2':
		camera->MoveDownward(0.1); break;
	case '9':
		camera->RotateY(-0.1); break;
	case '7':
		camera->RotateY(0.1); break;
	case '3':
		camera->RotateX(-0.1); break;
	case '1':
		camera->RotateX(0.1); break;
	case '4':
		camera->RotateZ(-0.1); break;
	case '6':
		camera->RotateZ(0.1); break;
	case ']':
		currentCamera++;
		if(currentCamera>=cameraTypeNumber)
			currentCamera=0;
		player->cameraType=cameraType[currentCamera];
		player->repositionCamera();
		break;
	case '[':
		currentCamera--;
		if(currentCamera<0)
			currentCamera=cameraTypeNumber-1;
		player->cameraType=cameraType[currentCamera];
		player->repositionCamera();
		break;
	default: break;
	}
	// redeseneaza scena
	glutPostRedisplay();
}

// handler taste speciale
void keyboard(int key , int x, int y)
{
	// cu stanga/dreapta/sus/jos se misca masina curent
	// cu F12 se intra/iese din modul fullscreen
	switch (key)
	{
	case GLUT_KEY_RIGHT : rightKeyPressed=true; break;
		
	case GLUT_KEY_LEFT : leftKeyPressed=true; break;

	case GLUT_KEY_DOWN : downKeyPressed=true; break;

	case GLUT_KEY_UP : upKeyPressed=true; break;
	
	case GLUT_KEY_F10: 
		if(fullscreen==false)
		{
			glutFullScreen();
			fullscreen=true;
		} else
		{
			glutReshapeWindow(1000,700);
			glutPositionWindow(100,100);
			fullscreen=false;
		}
		break;
	default: printf("Unrecognized special key pressed!\n");
	}
	
}

//Functie apelata atunci cand se elibereaza o tasta
void keyboardUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT : rightKeyPressed=false; break;
		
	case GLUT_KEY_LEFT : leftKeyPressed=false; break;

	case GLUT_KEY_DOWN : downKeyPressed=false; break;

	case GLUT_KEY_UP : upKeyPressed=false; break;
	}
}


// GLUT callback
//  called on mouse movement
void motion (int x, int y)
{
	float factor=300;
	//if(buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)
	//	camera->MoveLeft((x-mouseXClick)/factor);

	if(buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN && buttons[GLUT_RIGHT_BUTTON] == GLUT_UP)
		camera->Move((x-mouseXClick)/factor,-(y-mouseYClick)/factor,0);

	if(buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN && buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
	{
		camera->RotateX((y-mouseYClick)/factor);
		camera->RotateY((x-mouseXClick)/factor);		
	}

	mouseXClick=x;
	mouseYClick=y;
	// redeseneaza scena
	glutPostRedisplay();
}   


void mouse(int buton, int state, int x, int y)
{
  buttons[buton] = state;
  mouseXClick = x;
  mouseYClick = y; 
  	// redeseneaza scena
	glutPostRedisplay();
}


// functie pentru redimensionarea subferestrei jos dreapta
void reshapeSide(int w, int h)
{
	// viewport de dimensiuni date
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	// calculare aspect ratio ( Width/ Height )
	GLfloat aspect = (GLfloat) w / (GLfloat) h;

	// intram in modul proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// incarcam matrice de perspectiva 
	gluPerspective(45, aspect, 1.0, 70);
}

// functie de proiectie
void reshape(int w, int h)
{
	// viewport de dimensiuni date
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	// calculare aspect ratio ( Width/ Height )
	GLfloat aspect = (GLfloat) w / (GLfloat) h;

	// intram in modul proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// incarcam matrice de perspectiva 
	gluPerspective(45, aspect, 0.2, 70);


	// Fereastra aplicatiei a fost redimensionata : trebuie sa recream subfereastra
	if(sideWindow != -1)
		glutDestroyWindow(sideWindow);
	
	// Creeaza subfereastra
	//sideWindow = glutCreateSubWindow(mainWindow,w-SIDEWINDOW_WIDTH-10,h-SIDEWINDOW_HEIGHT-10,SIDEWINDOW_WIDTH,SIDEWINDOW_HEIGHT);
	sideWindow = glutCreateSubWindow(mainWindow,10,10,SIDEWINDOW_WIDTH,SIDEWINDOW_HEIGHT);	
 	
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeSide);
	//fara handleri de tastatura/mouse

	// pregatim o scena noua in opengl
	glClearColor(0.0, 0.0, 0.0, 0.0);	// stergem tot
	glEnable(GL_DEPTH_TEST);			// activam verificarea distantei fata de camera (a adancimii)
	glShadeModel(GL_FLAT);			// mod de desenare SMOOTH
	//glEnable(GL_LIGHTING);				// activam iluminarea
	glEnable(GL_NORMALIZE);				// activam normalizarea normalelor
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1000,700);
	glutInitWindowPosition(100,100);
	mainWindow=glutCreateWindow("Need For Speed");
	init();
	glutIdleFunc(update);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}