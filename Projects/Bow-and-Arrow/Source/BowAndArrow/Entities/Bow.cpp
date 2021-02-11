#include <BowAndArrow/Entities/Bow.h>

Bow::Bow(float x, float y, float radius) {
    this->x = x;
    this->y = y;
    this->radius = radius;
}

GLfloat Bow::getX()
{
    return this->x;
}

void Bow::setX(GLfloat x)
{
    this->x = x;
}

GLfloat Bow::getY()
{
    return this->y;
}

void Bow::setY(GLfloat y)
{
    this->y = y;
}

GLfloat Bow::getRadius()
{
    return this->radius;
}
