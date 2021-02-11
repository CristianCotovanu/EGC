#include "Laborator4.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;

	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;

	translateXJumpingCube = 0;
	angularStepJumpingCube = 0;

	translateXSun = 0;
	translateYSun = 0;
	translateZSun = 0;

	angularStepSun = 0;
	angularStepEarth = 0;
	angularStepMoon = 0;
}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(angularStepOX);
	modelMatrix *= Transform3D::RotateOY(angularStepOY);
	modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// Bonus1: Jumping Cube
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(translateXJumpingCube + JUMPING_STEP / 2, 0, -2);
	modelMatrix *= Transform3D::RotateOZ(angularStepJumpingCube);
	modelMatrix *= Transform3D::Translate(-JUMPING_STEP / 2, 0, -2);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// Bonus2: Solar System
	// Sun
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(translateXSun, translateYSun, translateZSun);
	modelMatrix *= Transform3D::RotateOY(angularStepSun);
	modelMatrix *= Transform3D::Scale(PLANET_SIZE / 1.5, PLANET_SIZE / 1.5, PLANET_SIZE / 1.5);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// Earth 
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(translateXSun, translateYSun, translateZSun);
	modelMatrix *= Transform3D::RotateOY(angularStepEarth);
	modelMatrix *= Transform3D::Translate(EARTH_TO_SUN_DIST, 0, 0);
	modelMatrix *= Transform3D::RotateOY(angularStepEarth);
	modelMatrix *= Transform3D::Scale(PLANET_SIZE / 2.5, PLANET_SIZE / 2.5, PLANET_SIZE / 2.5);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	// Moon 
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(translateXSun, translateYSun, translateZSun);
	modelMatrix *= Transform3D::RotateOY(angularStepEarth);
	modelMatrix *= Transform3D::Translate(EARTH_TO_SUN_DIST, 0, 0);
	modelMatrix *= Transform3D::RotateOY(angularStepMoon);
	modelMatrix *= Transform3D::Translate(MOON_TO_EARTH_DIST, 0, 0);
	modelMatrix *= Transform3D::Scale(PLANET_SIZE / 3.5, PLANET_SIZE / 3.5, PLANET_SIZE / 3.5);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	// Cube 1 movement
	if (window->KeyHold(GLFW_KEY_W))
	{
		translateZ -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S))
	{
		translateZ += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D))
	{
		translateX += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A))
	{
		translateX -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_R))
	{
		translateY -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_F))
	{
		translateY += deltaTime;
	}

	// Cube 2 scaling
	if (window->KeyHold(GLFW_KEY_1))
	{
		scaleX += deltaTime;
		scaleY += deltaTime;
		scaleZ += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_2))
	{
		scaleX -= deltaTime;
		scaleY -= deltaTime;
		scaleZ -= deltaTime;
	}

	// Cube 3 rotations
	if (window->KeyHold(GLFW_KEY_3))
	{
		angularStepOX -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_4))
	{
		angularStepOX += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_5))
	{
		angularStepOY -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_6))
	{
		angularStepOY += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_7))
	{
		angularStepOZ -= deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_8))
	{
		angularStepOZ += deltaTime;
	}

	// Bonus1: Jumping Cube
	angularStepJumpingCube -= deltaTime;
	if (angularStepJumpingCube <= -M_PI) {
		angularStepJumpingCube = 0;
		translateXJumpingCube += JUMPING_STEP;
	}

	// Bonus2: Solar System
	translateXSun += deltaTime / 5;
	translateYSun += deltaTime / 5;
	translateZSun += deltaTime / 5;
	angularStepEarth += deltaTime;
	angularStepMoon += deltaTime / 2;
	angularStepSun += deltaTime / 5;
	
}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
