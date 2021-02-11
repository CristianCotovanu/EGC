#pragma once

#include <Core/Engine.h>

class Arrow {
private:
	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;
	GLfloat chargeMeter;
	GLboolean moving;

public:
	Arrow(float x, float y, float width, float length);

	GLfloat getX();
	void setX(GLfloat x);

	GLfloat getY();
	void setY(GLfloat y);

	GLfloat getWidth();
	GLfloat getLength();
	
	GLboolean getChargeMeter();
	void setChargeMeter(GLfloat chargeMeter);
	void resetChargeMeter();

	GLboolean isMoving();
	void setMoving(GLboolean moving);
};