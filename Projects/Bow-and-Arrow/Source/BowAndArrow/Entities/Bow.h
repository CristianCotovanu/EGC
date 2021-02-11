#pragma once

#include <Core/Engine.h>

class Bow {
private:
	GLfloat x;
	GLfloat y;
	GLfloat radius;

public:
	Bow(float x, float y, float radius);

	GLfloat getX();
	void setX(GLfloat x);

	GLfloat getY();
	void setY(GLfloat y);
	
	GLfloat getRadius();
};
