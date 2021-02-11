#pragma once

#include <Core/Engine.h>

class HealthIndicator {
private:
	GLfloat x;
	GLfloat y;
	GLfloat radius;

public:
	HealthIndicator(float x, float y, float radius);

	GLfloat getX();
	GLfloat getY();
	GLfloat getRadius();
};
