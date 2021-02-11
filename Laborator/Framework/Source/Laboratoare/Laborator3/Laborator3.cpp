#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);

	// compute coordinates of square center
	float cx = corner.x + SQUARE_SIDE / 2;
	float cy = corner.y + SQUARE_SIDE / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;
	limitTranslation = true;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	limitScaling = true;

	// initialize angularStep
	angularStep = 0;

	Mesh* square1 = Object2D::CreateSquare("square1", corner, SQUARE_SIDE, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* square2 = Object2D::CreateSquare("square2", corner, SQUARE_SIDE, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, SQUARE_SIDE, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, SQUARE_SIDE / 2, glm::vec3(1, 1, 0), true);
	AddMeshToList(square4);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// Animation1: Move between top and bottom
	RenderSquare1UpAndDown(deltaTimeSeconds);
	// Animation2: Rotate around inner center
	RenderSquare2Spin(deltaTimeSeconds);
	// Animation3: Pulse a square size around center
	RenderSquare3PulseSize(deltaTimeSeconds);
	// Animation4: Square that orbits around the first blue square
	RenderSquare4Orbit(deltaTimeSeconds);
}

void Laborator3::RenderSquare1UpAndDown(float deltaTimeSeconds)
{
	if (limitTranslation) {
		if (translateY > 200)
			limitTranslation = false;

		translateY += deltaTimeSeconds * TRANSLATION_FACTOR;
	}
	else
	{
		if (translateY < -200)
			limitTranslation = true;

		translateY -= deltaTimeSeconds * TRANSLATION_FACTOR;
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150, 250);
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::RenderSquare2Spin(float deltaTimeSeconds)
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(400, 250);
	modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
	modelMatrix *= Transform2D::Rotate(angularStep += deltaTimeSeconds * ROTATION_FACTOR);
	modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::RenderSquare3PulseSize(float deltaTimeSeconds)
{
	if (limitScaling) {
		if (scaleX >= 2 && scaleY >= 2)
			limitScaling = false;

		scaleX += deltaTimeSeconds * SCALING_FACTOR;
		scaleY += deltaTimeSeconds * SCALING_FACTOR;
	}
	else
	{
		if (scaleX < 0.5 && scaleY < 0.5)
			limitScaling = true;

		scaleX -= deltaTimeSeconds * SCALING_FACTOR;
		scaleY -= deltaTimeSeconds * SCALING_FACTOR;
	}
	 
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(650, 250);
	modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::RenderSquare4Orbit(float deltaTimeSeconds)
{
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150, 250);
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
	modelMatrix *= Transform2D::Rotate(angularStep += deltaTimeSeconds * ROTATION_FACTOR);
	modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);
	modelMatrix *= Transform2D::Translate(ORBITING_DISTANCE, ORBITING_DISTANCE);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
