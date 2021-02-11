#pragma once

#include <Core/Engine.h>

class Sphere {
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat onPlatform;
	GLboolean inAir;
	GLboolean movingUpward;

	GLboolean deformation;
	GLfloat deformationTime;

public:
	Sphere();
	Sphere(float x, float y, float z);

	GLfloat getX();
	void setX(GLfloat x);

	GLfloat getY();
	void setY(GLfloat y);

	GLfloat getZ();
	void setZ(GLfloat z);

	GLboolean isInAir();
	void setInAir(GLboolean inAir);

	GLboolean isOnPlatform();
	void setOnPlatform(GLboolean onPlatform);

	GLboolean isMovingUp();
	void setMovingUp(GLboolean movingUpward);

	GLboolean isDeformed();
	void setDeformation(bool deformation);

	GLfloat getDeformationTime();
	void setDeformationTime(GLfloat deformationTime);
};