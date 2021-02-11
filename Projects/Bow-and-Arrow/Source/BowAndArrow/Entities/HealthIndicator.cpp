#include <BowAndArrow/Entities/HealthIndicator.h>

HealthIndicator::HealthIndicator(float x, float y, float radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}

GLfloat HealthIndicator::getX()
{
	return this->x;
}

GLfloat HealthIndicator::getY()
{
	return this->y;
}

GLfloat HealthIndicator::getRadius()
{
	return this->radius;
}
