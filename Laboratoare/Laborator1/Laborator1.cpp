#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
	UpdateClearColour();
	UpdateRenderedObject();
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	//RenderMesh(Mesh * mesh, glm::vec3 position, glm::vec3 scale)

	// Load a mesh from file into GPU memory
	{
		Mesh* boxMesh = new Mesh("box");
		boxMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[boxMesh->GetMeshID()] = boxMesh;
	}

	{
		Mesh* teapotMesh = new Mesh("teapot");
		teapotMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[teapotMesh->GetMeshID()] = teapotMesh;
	}
		
	{
		Mesh* archerMesh = new Mesh("oildrum");
		archerMesh->LoadMesh(RESOURCE_PATH::MODELS + "Props", "oildrum.obj");
		meshes[archerMesh->GetMeshID()] = archerMesh;
	}
		
	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo/", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(redFactor, greenFactor, blueFactor, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	// render extra object
	RenderMesh(meshes[objName], glm::vec3(objX, objY, objZ), glm::vec3(objScale));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W))
	{
		objZ -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_A))
	{
		objX -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S))
	{
		objZ += deltaTime;
	}
	
	if (window->KeyHold(GLFW_KEY_D))
	{
		objX += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_Q))
	{
		objY -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_E))
	{
		objY += deltaTime;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_X) {
		UpdateClearColour();
	}

	if (key == GLFW_KEY_Z) {
		UpdateRenderedObject();
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}

void Laborator1::UpdateClearColour() {
	if (colorReset) {
		redFactor = 0;
		greenFactor = 0;
		blueFactor = 0;
		colorReset = false;
	}
	else
	{
		redFactor = 0.25;
		greenFactor = 0.5;
		blueFactor = 0.2;
		colorReset = true;
	}
}

void Laborator1::UpdateRenderedObject() {
	++objIdx;
	objIdx %= EXTRA_OBJECTS;

	if (objIdx == 0) {
		objX = -1;
		objY = 1;
		objZ = 0;
		objName = "teapot";
		objScale = 1;
	}
	else if (objIdx == 1)
	{
		objX = -2;
		objY = 0;
		objZ = -2;
		objName = "bamboo";
		objScale = 0.2f;
	}
	else
	{
		objX = 1;
		objY = 0.75f;
		objZ = 0;
		objName = "oildrum";
		objScale = 0.5f;
	}
}
