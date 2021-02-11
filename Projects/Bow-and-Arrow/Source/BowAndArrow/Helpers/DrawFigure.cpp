#include "DrawFigure.h"

#include <Core/Engine.h>

Mesh* DrawFigure::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	Mesh* square = new Mesh(name);
	std::vector<GLushort> indices = { 0, 1, 2, 3 };
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length, width, 0), color),
		VertexFormat(glm::vec3(0, width, 0), color)
	};

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else 
	{
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* DrawFigure::CreateTriangle(std::string name, float width, float length, glm::vec3 color)
{
	Mesh* triangle = new Mesh(name);
	std::vector<GLushort> indices = { 0, 1, 2 };
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0,  0), color),
		VertexFormat(glm::vec3(length, width / 2,  0), color),
		VertexFormat(glm::vec3(0, width,  0), color)
	};
	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* DrawFigure::CreateBalloonThread(std::string name, float width, float height, glm::vec3 color)
{
	Mesh* line = new Mesh(name);
	std::vector<GLushort> indices = { 0, 1, 1, 2, 2, 3, 3, 4 };
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(width, height * 2,  0), color),
		VertexFormat(glm::vec3(0, height,  0), color),
		VertexFormat(glm::vec3(width, height * 2,  0), color),
		VertexFormat(glm::vec3(0, height, 0), color),
		VertexFormat(glm::vec3(width, 0, 0), color),
	};
	line->InitFromData(vertices, indices);
	line->SetDrawMode(GL_LINES);
	return line;
}

Mesh* DrawFigure::CreateBow(std::string name, float radius, glm::vec3 color)
{
	Mesh* bow = new Mesh(name);
	std::vector<GLushort> indices;
	std::vector<VertexFormat> vertices;
	GLint line = 0;
	for (float angle = 0.0f; angle <= M_PI; angle += 0.01f)
	{
		vertices.emplace_back(glm::vec3(sin(angle) * radius / 2.f, cos(angle) * radius, 0), color);
		indices.push_back(line++);
	}

	bow->InitFromData(vertices, indices);
	bow->SetDrawMode(GL_LINE_LOOP);
	return bow;
}

Mesh* DrawFigure::CreateArrow(std::string name, float height, float width, glm::vec3 color, bool fill)
{
	Mesh* square = new Mesh(name);
	std::vector<GLushort> indices = { 0, 1, 2, 3, 0, 2, 4, 6, 5 };
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, height, 0), color),
		VertexFormat(glm::vec3(0, height + 2, 0), color),
		VertexFormat(glm::vec3(width, height + 2, 0), color),
		VertexFormat(glm::vec3(width, height, 0), color),
		VertexFormat(glm::vec3(width, height + 6, 0), color),
		VertexFormat(glm::vec3(width + 20, height + 1, 0), color),
		VertexFormat(glm::vec3(width, 0, 0), color),
	};

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* DrawFigure::CreateBalloon(std::string name, float radius, glm::vec3 color)
{
	Mesh* balloon = new Mesh(name);
	std::vector<GLushort> indices;
	std::vector<VertexFormat> vertices;
	GLint line = 0;
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01)
	{
		vertices.emplace_back(glm::vec3(sin(angle) * radius / 1.75f, cos(angle) * radius, 0), color);
		indices.push_back(line++);
	}
	balloon->InitFromData(vertices, indices);
	balloon->SetDrawMode(GL_POLYGON);
	return balloon;
}

Mesh* DrawFigure::CreateCircle(std::string name, float radius, glm::vec3 color)
{
	Mesh* circle = new Mesh(name);
	std::vector<GLushort> indices;
	std::vector<VertexFormat> vertices;
	GLint line = 0;
	for (GLfloat angle = 0.0; angle <= 2 * M_PI; angle += 0.01)
	{
		vertices.emplace_back(glm::vec3(sin(angle) * radius, cos(angle) * radius, 0), color);
		indices.push_back(line++);
	}
	circle->InitFromData(vertices, indices);
	circle->SetDrawMode(GL_POLYGON);
	return circle;
}

Mesh* DrawFigure::CreateShuriken(std::string name, float width, float length, float height, glm::vec3 color)
{
	Mesh* shuriken = new Mesh(name);
	std::vector<GLushort> indices = {
		0, 1, 2,
		0, 3, 4,
		5, 6, 0,
		0, 7, 8
	};
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(width, length,  0), color),
		VertexFormat(glm::vec3(0, length + 20,  0), color),
		VertexFormat(glm::vec3(width, length + 20,  0), color),
		VertexFormat(glm::vec3(height, length + 20,  0), color),
		VertexFormat(glm::vec3(height, length,  0), color),
		VertexFormat(glm::vec3(height, 0,  0), color),
		VertexFormat(glm::vec3(width, 0,  0), color),
		VertexFormat(glm::vec3(0, 0,  0), color),
		VertexFormat(glm::vec3(0, length,  0), color)
	};

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}
