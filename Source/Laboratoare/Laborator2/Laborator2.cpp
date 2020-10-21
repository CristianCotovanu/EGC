#include "Laborator2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{

}

void Laborator2::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 0)),	// 0
			VertexFormat(glm::vec3(0, -1,  1), glm::vec3(0, 1, 0)),		// 1
			VertexFormat(glm::vec3(-1, 0,  1), glm::vec3(1, 0, 0)),		// 2
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(1, 0, 0)),		// 3

			VertexFormat(glm::vec3(-1, -1,  0), glm::vec3(0, 1, 0)),	// 4
			VertexFormat(glm::vec3(0, -1,  0), glm::vec3(0, 1, 0)),		// 5
			VertexFormat(glm::vec3(-1, 0,  0), glm::vec3(1, 0, 0)),		// 6
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 0, 0)),		// 7
		};

		vector<GLushort> indices =
		{
			0, 1, 2,	// 1
			1, 3, 2,	// 2

			1, 5, 7,	// 3
			1, 7, 3,	// 4

			3, 7, 2,	// 5
			2, 7, 6,	// 6

			7, 5, 4,	// 7
			6, 7, 4,	// 8

			2, 6, 4,	// 9
			2, 4, 0,	// 10

			0, 4, 1,	// 11
			1, 4, 5		// 12
		};

		meshes["testCube"] = new Mesh("Test mesh creation");
		meshes["testCube"]->InitFromData(vertices, indices);

		// Create a new mesh from buffer data
		Mesh* cube = CreateMesh("cube", vertices, indices);
	}

	// Create a mesh pyramid using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1, 3.5f, -2), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1.5, 1,  -0.5), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(3, 0,  0.5), glm::vec3(1, 0, 0)),
		};

		vector<GLushort> indices =
		{
			1, 2, 0,
			2, 3, 0,
			0, 3, 1,
			1, 3, 2
		};

		Mesh* pyramid = CreateMesh("pyramid", vertices, indices);
	}

	// Create a mesh square using custom data
	{
		vector<VertexFormat> squareVertices
		{
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 0,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(0, 1,  1), glm::vec3(1, 1, 0)),
		};

		vector<GLushort> squareIndices =
		{
			0, 2, 1,
			3, 0, 2
		};

		Mesh* square = CreateMesh("square", squareVertices, squareIndices);
	}

	// Create a mesh circle using custom data
	{
		vector<VertexFormat> circleVertices;
		vector<GLushort> circleIndices;

		int NUM_TRIANGLES = 20;
		double PI = 3.1415926535897932384626433832795;

		for (int a = 0; a < 360; a += 360 / NUM_TRIANGLES)
		{
			double heading = a * PI / 180;
			int radius = 1;
			circleVertices.push_back(VertexFormat(glm::vec3(cos(heading) * radius, sin(heading) * radius, 0)));
		}

		// Create a new mesh from buffer data
		Mesh* circle = CreateMesh("circle", circleVertices, circleIndices);
		meshes["circle"]->SetDrawMode(GL_LINE_LOOP);
	}
}

Mesh* Laborator2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<GLushort>& indices)
{
	// Create the VAO and bind it
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Create the IBO and bind it
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<GLushort>(indices.size()));
	return meshes[name];
}

void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Set culling to either Front or Back based on cullFace value
	glCullFace(cullFace);

	// Render an object using face normals for color
	RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(1, 0.5f, -1.5f), glm::vec3(0.75f));

	// Render an object using colors from vertex
	RenderMesh(meshes["testCube"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));

	RenderMesh(meshes["cube"], shaders["VertexColor"], glm::vec3(1.5f, 0.5f, 0), glm::vec3(0.25f));

	RenderMesh(meshes["pyramid"], shaders["VertexColor"], glm::vec3(-2, 0, -2), glm::vec3(0.5f));

	RenderMesh(meshes["square"], shaders["VertexColor"], glm::vec3(-3, 1, -1.5f), glm::vec3(0.5f));

	RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(2, 2, 0), glm::vec3(0.25f));

	// Disable face culling
	glDisable(GL_CULL_FACE);
}

void Laborator2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator2::OnKeyPress(int key, int mods)
{
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
	else if (key == GLFW_KEY_F2) {
		UpdateCullPerspective();
	}
}

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator2::OnWindowResize(int width, int height)
{
}

void Laborator2::UpdateCullPerspective() {
	if (cullFace == GL_BACK) {
		cullFace = GL_FRONT;
	}
	else
	{
		cullFace = GL_BACK;
	}
}
