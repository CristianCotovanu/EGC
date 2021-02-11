#include <BowAndArrow/Entities/Balloon.h>
#include <BowAndArrow\Constants\Constants.cpp>

Balloon::Balloon(float x, float y, float radius, bool evil) {
	this->x = x;
	this->y = y;
	this->scaleY = 1.f;
	this->radius = radius;
	this->evil = evil;
	this->popped = false;
	this->speed = BalloonConstants::speed;
}

void Balloon::pop()
{
	this->y = this->y - 100;
	this->scaleY = 0.5f;
	this->popped = true;
	this->speed = this->speed * -3 / 4;
}

void Balloon::respawn(int maxX, int maxY)
{
	this->x = rand() % maxX + BalloonConstants::safetyMargin;
	this->y = rand() % maxY - maxY;
	this->scaleY = 1;
	this->popped = false;
	this->speed = BalloonConstants::speed;
}

GLfloat Balloon::getX()
{
    return this->x;
}

void Balloon::setX(GLfloat x)
{
	this->x = x;
}

GLfloat Balloon::getY()
{
	return this->y;
}

void Balloon::setY(GLfloat y)
{
	this->y = y;
}

GLfloat Balloon::getScaleY()
{
	return this->scaleY;
}

void Balloon::setScaleY(GLfloat y)
{
	this->scaleY = y;
}

GLfloat Balloon::getRadius()
{
	return this->radius;
}

GLfloat Balloon::getSpeed()
{
	return this->speed;
}

void Balloon::setSpeed(GLfloat speed)
{
	this->speed = speed;
}

GLboolean Balloon::isEvil()
{
	return this->evil;
}

void Balloon::setPopped(GLboolean popped)
{
	this->popped = popped;
}

GLboolean Balloon::isPopped()
{
	return this->popped;
}
