#include "Platform.h"
#include <Laboratoare\Skyroads\Constants\Constants.cpp>

Platform::Platform(GLfloat x, GLfloat y, GLfloat tempZ)
{
	this->x = x;
	this->y = y;
	this->scaleZ = rand() % 8 + 3;
	this->z = tempZ - this->scaleZ / 2.f - rand() % 2;
	this->color = rand() % 5;
}

void Platform::reinitializePlatform(std::vector<Platform*>& platformsVector)
{
	this->scaleZ = rand() % 8 + 3;
	this->z = platformsVector[PlatformConstants::count - 2]->getZ()
		- platformsVector[PlatformConstants::count - 2]->getScaleZ() / 2.f
		- this->scaleZ / 2.f
		- rand() % 2;
	this->color = rand() % 5;
}

GLfloat Platform::getX()
{
	return this->x;
}

void Platform::setX(GLfloat x)
{
	this->x = x;
}

GLfloat Platform::getY()
{
	return this->y;
}

void Platform::setY(GLfloat y)
{
	this->y = y;
}

GLfloat Platform::getZ()
{
	return this->z;
}

void Platform::setZ(GLfloat z)
{
	this->z = z;
}

GLfloat Platform::getScaleZ()
{
	return this->scaleZ;
}

void Platform::setScaleZ(GLfloat scaleZ)
{
	this->scaleZ = scaleZ;
}

GLint Platform::getColor()
{
	return this->color;
}

void Platform::setColor(GLint color)
{
	this->color = color;
}
