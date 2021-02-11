#pragma once

#include <Core/Engine.h>

class Balloon {
private:
	GLfloat x;
	GLfloat y;
	GLfloat radius;
	GLfloat speed;
	GLboolean evil;
	GLboolean popped;
	GLfloat scaleY;

public:
	Balloon(float x, float y, float radius, bool evil);

	void pop();
	void respawn(int maxX, int maxY);

	GLfloat getX();
	void setX(GLfloat x);
	
	GLfloat getY();
	void setY(GLfloat y);
	
	GLfloat getScaleY();
	void setScaleY(GLfloat y);

	GLfloat getRadius();

	GLfloat getSpeed();
	void setSpeed(GLfloat speed);

	GLboolean isEvil();
	GLboolean isPopped();
	void setPopped(GLboolean popped);
};
