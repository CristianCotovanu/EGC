#pragma once

#include <Core/Engine.h>

class Platform {
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat scaleZ;
	GLint color;

public:
	Platform(GLfloat x, GLfloat y, GLfloat tempZ);

	void reinitializePlatform(std::vector<Platform*>& platformsVector);

	GLfloat getX();
	void setX(GLfloat x);

	GLfloat getY();
	void setY(GLfloat y);

	GLfloat getZ();
	void setZ(GLfloat z);

	GLfloat getScaleZ();
	void setScaleZ(GLfloat scaleZ);

	GLint getColor();
	void setColor(GLint color);
};
