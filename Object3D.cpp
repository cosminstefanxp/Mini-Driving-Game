// EGC
// Laborator 6
//-------------------------------------------------

#include "Object3D.h"

/*
Declaratiile clasei Object3D
Clasa pentru desenare si modificare a unui obiect 3d.
*/

// VARIABILE STATICE
//-------------------------------------------------
//float *Vector3D::arr = new float[3];
Vector3D Object3D::SelectedColor = Vector3D(1,0,1);		// culoarea obiectului selectat
Vector3D Object3D::ColorIncrement = Vector3D(0.04,0.04,0.04);	// valoarea cu care creste/scade in timp culoarea de mai sus


// CONSTRUCTORI
//-------------------------------------------------

// constructor de baza
Object3D::Object3D()
{
	defaultSettings();
}

// seteaza si tipul obiectului
Object3D::Object3D(ObjectType _Type)
{
	defaultSettings();
	Type = _Type;
}

// seteaza si pozitia
Object3D::Object3D(Vector3D *_translation)
{
	defaultSettings();
	this->SetPosition(_translation);
}

// seteaza pozitie, rotatie, translatie
Object3D::Object3D(Vector3D *_translation, Vector3D *_rotation, Vector3D *_scale)
{
	defaultSettings();
	this->SetPosition(_translation);
	this->SetRotation(_rotation);
	this->SetScale(_scale);	
}

// seteaza toti parametrii la valorile lor default
void Object3D::defaultSettings()
{
	translation = Vector3D(0.0,0.0,0.0);
	rotation = Vector3D(0.0,0.0,0.0);
	scale = Vector3D(1.0,1.0,1.0);
	this->diffuse = Vector4D(0,0,0,0);
	this->color = Vector3D(1,1,1);

	Lighted = true;
	Wireframe = false;
	Visible = true;
	Type = Custom;

	levelOfDetail = 12;
	selected = false;

	cylinderQuadric=gluNewQuadric();

	//Bounding box
	this->boundingBox=new BoundingBox(&translation);
	this->CollisionEnabled=true;
}

// DRAW
//-------------------------------------------------
void Object3D::Draw ()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
	return;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// setari de material :
	// daca nu este selectat
	if( !selected )
	{
		// culoare normala
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,diffuse.Array());
	}
	else
	{
		// culoarea atunci cand obiectul este selectat
		glColor3f(SelectedColor.x, SelectedColor.y, SelectedColor.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(SelectedColor.x,SelectedColor.y,SelectedColor.z,1)).Array());
	}
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1,0.1,0.1,1)).Array());

	// daca este wireframe
	if( Wireframe )
		switch( Type )
	{
		// cub wireframe
		case Cube :	glutWireCube(1.0); break;
		// sfera wireframe
		case Sphere : glutWireSphere(1.0, levelOfDetail, levelOfDetail); break;
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}
	// daca nu este wireframe
	else
		switch( Type )
	{
		//tetraedru
		case Tetrahedron : glutSolidTetrahedron();
		//dodecaedru
		case Dodecahedron : glutSolidDodecahedron();
		// ibric
		case Teapot : glutSolidTeapot(1); break;
		// con solid
		case Cone : glutSolidCone(1.0,2,levelOfDetail,levelOfDetail); break;
		// cub solid
		case Cube :	glutSolidCube(1.0); break;
		// sfera solida
		case Sphere : glutSolidSphere(1.0, levelOfDetail, levelOfDetail); break;
		// cilindru
		case Cylinder: gluCylinder(cylinderQuadric,1,1,1,levelOfDetail,levelOfDetail); break;
		// tor
		case Torus: glutSolidTorus(0.7,1,levelOfDetail,levelOfDetail);
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}

	glPopMatrix();
}

// functie proprie
// se presupune ca Wireframe este tratat inauntru
void Object3D::customDraw()
{
	// TODO : aici va puteti desena un obiect personalizat/incarcat din fisier/pre-generat/etc
}

// SETTERS
//-------------------------------------------------

// selecteaza
void Object3D::Select()
{
	selected = true;
}

// deselecteaza
void Object3D::Deselect()
{
	selected = false;
}

// seteaza culoare
void Object3D::SetColor(Vector3D *_color)
{
	color = *_color;
}

// seteaza pozitie
void Object3D::SetPosition(Vector3D *_translation)
{
	translation = *_translation;
}

// seteaza rotatie
void Object3D::SetRotation(Vector3D *_rotation)
{
	rotation = *_rotation;
}

// seteaza scalare
void Object3D::SetScale(Vector3D *_scale)
{
	scale = *_scale;
	boundingBox->minX *= _scale->x;
	boundingBox->minY *= _scale->y;
	boundingBox->minZ *= _scale->z;

	boundingBox->maxX *= _scale->x;
	boundingBox->maxY *= _scale->y;
	boundingBox->maxZ *= _scale->z;
}

// seteaza nivelul de detaliu
void Object3D::SetLevelOfDetail(float _levelOfDetail)
{
	if( _levelOfDetail > 0 && _levelOfDetail < MAXIMUM_LOD)
		levelOfDetail = _levelOfDetail;
}


// GETTERS
//-------------------------------------------------

// intoarce pozitia
Vector3D Object3D::GetPosition()
{
	return translation;
}

// intoarce rotatia
Vector3D Object3D::GetRotation()
{
	return rotation;
}

// intoarce scala
Vector3D Object3D::GetScale()
{
	return scale;
}

// intoarce nivelul de detaliu
float Object3D::GetLevelOfDetail()
{
	return levelOfDetail;
}

void Object3D::setBoundingBoxMargin(float _maxX,float _maxY, float _maxZ, float _minX, float _minY, float _minZ)
{
	this->boundingBox->minX=_minX;
	this->boundingBox->minY=_minY;
	this->boundingBox->minZ=_minZ;

	this->boundingBox->maxX=_maxX;
	this->boundingBox->maxY=_maxY;
	this->boundingBox->maxZ=_maxZ;
}

bool Object3D::isCollision(Object3D *otherObj)
{
	if(this->CollisionEnabled==false || otherObj->CollisionEnabled==false)
		return false;
	//Calcul de coliziune
	if(this->boundingBox->isCollision(otherObj->boundingBox))
		return true;
	return false;

}