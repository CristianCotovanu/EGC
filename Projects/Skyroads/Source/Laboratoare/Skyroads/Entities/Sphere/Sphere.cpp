#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->inAir = false;
    this->onPlatform = false;
    this->movingUpward = false;
    this->deformation = false;
    this->deformationTime = 0;
}

GLfloat Sphere::getX()
{
    return this->x;
}

void Sphere::setX(GLfloat x)
{
    this->x = x;
}

GLfloat Sphere::getY()
{
    return this->y;
}

void Sphere::setY(GLfloat y)
{
    this->y = y;
}

GLfloat Sphere::getZ()
{
    return this->z;
}

void Sphere::setZ(GLfloat z)
{
    this->z = z;
}

GLboolean Sphere::isInAir()
{
    return this->inAir;
}

void Sphere::setInAir(GLboolean inAir)
{
    this->inAir = inAir;
}

GLboolean Sphere::isOnPlatform()
{
    return this->onPlatform;
}

void Sphere::setOnPlatform(GLboolean onPlatform)
{
    this->onPlatform = onPlatform;
}

GLboolean Sphere::isMovingUp()
{
    return this->movingUpward;
}

void Sphere::setMovingUp(GLboolean movingUpward)
{
    this->movingUpward = movingUpward;
}

GLboolean Sphere::isDeformed()
{
    return this->deformation;
}

void Sphere::setDeformation(bool deformation)
{
    this->deformation = deformation;
}

GLfloat Sphere::getDeformationTime()
{
    return this->deformationTime;
}

void Sphere::setDeformationTime(GLfloat deformationTime)
{
    this->deformationTime = deformationTime;
}
