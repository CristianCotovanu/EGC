#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace DrawFigure
{
	Mesh* CreateTriangle(std::string name, float width, float length, glm::vec3 color);
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
	Mesh* CreateBalloon(std::string name, float radius, glm::vec3 color);

	Mesh* CreateCircle(std::string name, float radius, glm::vec3 color);
	
	Mesh* CreateBalloonThread(std::string name, float width, float height, glm::vec3 color);
	Mesh* CreateBow(std::string name, float radius, glm::vec3 color);
	Mesh* CreateArrow(std::string name, float height, float width, glm::vec3 color, bool fill);
	Mesh* CreateShuriken(std::string name, float width, float length, float width2, glm::vec3 color);
}
