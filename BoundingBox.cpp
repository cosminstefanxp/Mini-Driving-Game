#include "BoundingBox.h"

BoundingBox::BoundingBox(Vector3D *_position)
{
	this->maxX=1;
	this->maxY=1;
	this->maxZ=1;

	this->minX=-1;
	this->minY=-1;
	this->minZ=-1;

	this->position=_position;

}

BoundingBox::~BoundingBox(void)
{
}

bool BoundingBox::isCollision(BoundingBox* otherBB)
{
	if (this->maxX + this->position->x < otherBB->minX+ otherBB->position->x ) return false;
    if (this->minX + this->position->x > otherBB->maxX+ otherBB->position->x) return false;

	if (this->maxY + this->position->y < otherBB->minY+ otherBB->position->y) return false;
	if (this->minY + this->position->y > otherBB->maxY+ otherBB->position->y) return false;

	if (this->maxZ + this->position->z < otherBB->minZ+ otherBB->position->z) return false;
	if (this->minZ + this->position->z > otherBB->maxZ+ otherBB->position->z) return false;

	return true;
}
