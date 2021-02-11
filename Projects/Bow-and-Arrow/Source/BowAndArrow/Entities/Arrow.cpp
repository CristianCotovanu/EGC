#include <BowAndArrow/Entities/Arrow.h>

Arrow::Arrow(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->chargeMeter = 0;
	this->moving = false;
}

GLfloat Arrow::getX()
{
	return this->x;
}

void Arrow::setX(GLfloat x)
{
	this->x = x;
}

GLfloat Arrow::getY()
{
	return this->y;
}

void Arrow::setY(GLfloat y)
{
	this->y = y;
}

GLfloat Arrow::getWidth()
{
	return this->width;
}

GLfloat Arrow::getLength()
{
	return this->height;
}

GLboolean Arrow::getChargeMeter()
{
	return this->chargeMeter;
}

void Arrow::setChargeMeter(GLfloat chargeMeter)
{
	this->chargeMeter = chargeMeter;
}

void Arrow::resetChargeMeter()
{
	this->chargeMeter = 0;
}

GLboolean Arrow::isMoving()
{
	return this->moving;
}

void Arrow::setMoving(GLboolean moving)
{
	this->moving = moving;
}
