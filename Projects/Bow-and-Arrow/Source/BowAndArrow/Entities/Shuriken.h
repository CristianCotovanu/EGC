#pragma once

#include <Core/Engine.h>

class Shuriken {
private:
	GLfloat x;
	GLfloat y;
	GLfloat radius;
	GLfloat rotationStep;

public:
	Shuriken(float x, float y, float radius);

	void respawn(int maxX, int maxY);

	GLfloat getX();
	void setX(GLfloat x);

	GLfloat getY();
	void setY(GLfloat y);

	GLfloat getRadius();

	GLfloat getRotationStep();
	void setRotationStep(GLfloat rotationStep);
};