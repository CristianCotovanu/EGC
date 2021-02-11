#include <BowAndArrow/Entities/Shuriken.h>
#include <BowAndArrow/Constants/Constants.cpp>

Shuriken::Shuriken(float x, float y, float radius) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->rotationStep = ShurikenConstants::initialRotationStep;
}

void Shuriken::respawn(int maxX, int maxY)
{
	this->x = rand() % maxX + ShurikenConstants::safetyMargin;
	this->y = rand() % maxY;
}

GLfloat Shuriken::getX()
{
	return this->x;
}

void Shuriken::setX(GLfloat x)
{
	this->x = x;
}

GLfloat Shuriken::getY()
{
	return this->y;
}

void Shuriken::setY(GLfloat y)
{
	this->y = y;
}

GLfloat Shuriken::getRadius()
{
	return this->radius;
}

GLfloat Shuriken::getRotationStep()
{
	return this->rotationStep;
}

void Shuriken::setRotationStep(GLfloat rotationStep)
{
	this->rotationStep = rotationStep;
}

