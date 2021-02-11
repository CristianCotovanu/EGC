#include "Skyroads.h"

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include <Core/Engine.h>
#include <Laboratoare\Skyroads\Helpers\Transform.h>
#include <Laboratoare\Skyroads\Constants\Constants.cpp>
#include <Laboratoare\Skyroads\Entities\Platform\Platform.h>

using namespace std;

Skyroads::Skyroads()
{
}

Skyroads::~Skyroads()
{
}

void Skyroads::Init()
{
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("cube");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* fuelbar = Transform::CreateRectangle("fuel", 1.2f, 0.1f, glm::vec3(1.f, 0.f, 0.f), true);
		meshes[fuelbar->GetMeshID()] = fuelbar;
	}

	{
		Shader* shader = new Shader("Shader");
		shader->AddShader("Source/Laboratoare/Skyroads/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Skyroads/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	platformsSpeed = 2;

	time = 0;

	fuelBarNewPosition = 1;
	stepFuelBar = 0.0003f;
	currentFuel = 1;

	noRespawnSafeTime = 0;
	speedActivated = false;
	gameOverFall = false;

	crtPlatformNumber = 0;
	cameraType = 0;
	
	sphere = new Sphere(0, 0.9f + PlatformConstants::scaleY, 1.5f);

	lastPlatformCenterZ = sphere->getZ();
	lastPlatformCenterScaleZ = 0;

	lastPlatformRightZ = sphere->getZ();
	lastPlatformRightScaleZ = 0;

	lastPlatformLeftZ = sphere->getZ();
	lastPlatformLeftScaleZ = 0;

	for (int i = 0; i < PlatformConstants::count; i++) {
		platformsRight.push_back(new Platform(PlatformConstants::scaleX, 0.75f, lastPlatformRightZ - lastPlatformRightScaleZ / 2.f));
		lastPlatformRightZ = platformsRight[i]->getZ();
		lastPlatformRightScaleZ = platformsRight[i]->getScaleZ();
		
		platformsLeft.push_back(new Platform(-PlatformConstants::scaleX, 0.75f, lastPlatformLeftZ - lastPlatformLeftScaleZ / 2.f));
		lastPlatformLeftZ = platformsLeft[i]->getZ();
		lastPlatformLeftScaleZ = platformsLeft[i]->getScaleZ();
		
		platformsCenter.push_back(new Platform(0, 0.75f, lastPlatformCenterZ - lastPlatformCenterScaleZ / 2.f));
		lastPlatformCenterZ = platformsCenter[i]->getZ();
		lastPlatformCenterScaleZ = platformsCenter[i]->getScaleZ();
	}
}

void Skyroads::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Skyroads::Update(float deltaTimeSeconds)
{
	if (cameraType != 0)
		SetFirstPerson();
	else
		SetThirdPerson();

	noRespawnSafeTime++;

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(sphere->getX(), sphere->getY(), sphere->getZ()));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));

		if (sphere->isDeformed()) {
			sphere->setDeformationTime(sphere->getDeformationTime() + 1);
			RenderCustomMesh(meshes["sphere"], shaders["Shader"], modelMatrix, glm::vec3(0.75f, 0.75f, 0.75f));
			if (sphere->getDeformationTime() > 200) {
				sphere->setDeformationTime(0);
				sphere->setDeformation(false);
			}
		}
		else 
		{
			RenderSimpleMesh(meshes["sphere"], shaders["Shader"], modelMatrix, glm::vec3(0.75f, 0.75f, 0.75f));
		}
	}

	currentFuel -= stepFuelBar;

	if (currentFuel < 0) {
		currentFuel = 0;
	}

	for (int i = 0; i < PlatformConstants::count && gameOverFall == false; i++) {
		platformsLeft[i]->setZ(platformsLeft[i]->getZ() + platformsSpeed * deltaTimeSeconds);
		platformsRight[i]->setZ(platformsRight[i]->getZ() + platformsSpeed * deltaTimeSeconds);
		platformsCenter[i]->setZ(platformsCenter[i]->getZ() + platformsSpeed * deltaTimeSeconds);

		GeneratePlatforms(platformsLeft[i]);
		GeneratePlatforms(platformsCenter[i]);
		GeneratePlatforms(platformsRight[i]);

		CheckPlatformIsOut(platformsLeft);		// if left platform is out
		CheckPlatformIsOut(platformsCenter);	// if center platform is out
		CheckPlatformIsOut(platformsRight);		// if right platform is out
	}

	if (speedActivated == true) {
		platformsSpeed = 6;
		time++;
	}

	if (time > 800 && speedActivated == true) {
		speedActivated = false;
		platformsSpeed = 2;
		time = 0;
	}

	if (crtPlatformNumber == -1 
		&& sphere->getZ() > platformsLeft[0]->getZ() - platformsLeft[0]->getScaleZ() / 2.f - 0.5f
		&& sphere->getZ() < platformsLeft[0]->getZ() + platformsLeft[0]->getScaleZ() / 2.f + 0.5f)
	{
		ApplyPlatformEffectOnSphere(platformsLeft[0]);
	}
	else if (crtPlatformNumber == 0 
		&& sphere->getZ() > platformsCenter[0]->getZ() - platformsCenter[0]->getScaleZ() / 2.f - 0.5f
		&& sphere->getZ() < platformsCenter[0]->getZ() + platformsCenter[0]->getScaleZ() / 2.f + 0.5f)
	{
		ApplyPlatformEffectOnSphere(platformsCenter[0]);
	}
	else if (crtPlatformNumber == 1 
		&& sphere->getZ() > platformsRight[0]->getZ() - platformsRight[0]->getScaleZ() / 2.f - 0.5f 
		&& sphere->getZ() < platformsRight[0]->getZ() + platformsRight[0]->getScaleZ() / 2.f + 0.5f)
	{
		ApplyPlatformEffectOnSphere(platformsRight[0]);
	}
	else
	{
		if (!sphere->isInAir() && noRespawnSafeTime > 400)
		{
			gameOverFall = true;
			sphere->setY(sphere->getY() - 0.5f * deltaTimeSeconds);
		}
	}

	// verificare y pe platforme
	if ((crtPlatformNumber == -1 && sphere->getY() > platformsLeft[0]->getY() + 0.25f)
		|| (crtPlatformNumber == 0 && sphere->getY() > platformsCenter[0]->getY() + 0.25f)
		|| (crtPlatformNumber == 1 && sphere->getY() > platformsRight[0]->getY() + 0.25f))
		sphere->setInAir(true);
	else 
		sphere->setInAir(false);

	if (platformsSpeed < 2)
		platformsSpeed = 2;

	if (sphere->isMovingUp())
		sphere->setY(sphere->getY() + 0.5f * deltaTimeSeconds);		// in urcare
	else
		sphere->setY(sphere->getY() - 0.5f * deltaTimeSeconds);		// in coborare

	if (sphere->getY() > 1.2f) // daca a ajuns la inaltimea maxima
		sphere->setMovingUp(false);

	if (sphere->getY() < 0.9f + PlatformConstants::scaleY && gameOverFall == false)	// sa nu coboare prea mult
		sphere->setY(0.9f + PlatformConstants::scaleY);

	if (sphere->getY() < -0.3f && noRespawnSafeTime > 400)
	{
		cout << "GAME OVER!" << "\n";
		exit(0);
	}

	if (cameraType != 0)	// first person
	{
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform::Translate(sphere->getX(), sphere->getY() + 0.225f);
		modelMatrix *= Transform::Scale(currentFuel, 0.5f);
		RenderMesh2D(meshes["fuel"], shaders["VertexColor"], modelMatrix);
	}
	else 
	{
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transform::Translate(1.6f, 2.71f);
		modelMatrix *= Transform::Scale(currentFuel, 1);
		RenderMesh2D(meshes["fuel"], shaders["VertexColor"], modelMatrix);
	}

	// daca nu in afara platformelor
	if (sphere->getX() != 0 
		&& sphere->getX() != PlatformConstants::scaleX 
		&& sphere->getX() != -PlatformConstants::scaleX 
		&& noRespawnSafeTime > 400) {
		cout << "GAME OVER!" << endl;
		exit(0);
	}

	if (currentFuel <= 0) {
		cout << "GAME OVER!" << endl;
		exit(0);
	}
}

void Skyroads::FrameEnd()
{
	DrawCoordinatSystem();
}

void Skyroads::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);
	int location;

	location = glGetUniformLocation(shader->program, "object_color");
	glUniform3f(location, color.x, color.y, color.z);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	GLint t = glGetUniformLocation(shader->program, "time");
	glUniform1f(t, 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Skyroads::RenderCustomMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	int location = glGetUniformLocation(shader->program, "object_color");
	glUniform3f(location, color.x, color.y, color.z);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	GLint t = glGetUniformLocation(shader->program, "time");
	glUniform1f(t, (GLfloat)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Skyroads::OnInputUpdate(float deltaTime, int mods)
{

}

void Skyroads::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C) 
	{
		cameraType++;
		cameraType %= 2;
	}

	// add key press event
	if (key == GLFW_KEY_W && speedActivated == false) 
	{
		platformsSpeed += 3.f;
	}
	else if (key == GLFW_KEY_S && speedActivated == false) 
	{
		platformsSpeed -= 3.f;
	}

	if (key == GLFW_KEY_A) 
	{
		sphere->setX(sphere->getX() - PlatformConstants::scaleX);
		crtPlatformNumber -= 1;
	}
	else if (key == GLFW_KEY_D) 
	{
		sphere->setX(sphere->getX() + PlatformConstants::scaleX);
		crtPlatformNumber += 1;
	}
	
	if (key == GLFW_KEY_SPACE && !sphere->isInAir())
	{
		sphere->setMovingUp(true);
		sphere->setInAir(true);
	}
}

void Skyroads::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Skyroads::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Skyroads::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Skyroads::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Skyroads::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Skyroads::OnWindowResize(int width, int height)
{
}

void Skyroads::GeneratePlatforms(Platform* platform)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(platform->getX(), platform->getY(), platform->getZ()));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(PlatformConstants::scaleX, PlatformConstants::scaleY, platform->getScaleZ()));

	switch (platform->getColor()) {
	case ColorConstants::red:
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, glm::vec3(1, 0, 0));
		break;
	case ColorConstants::yellow:
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, glm::vec3(1, 1, 0));
		break;
	case ColorConstants::orange:
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, glm::vec3(1, 0.5f, 0));
		break;
	case ColorConstants::green:
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, glm::vec3(0, 1, 0));
		break;
	case ColorConstants::blue:
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, glm::vec3(0, 0, 1));
		break;
	case ColorConstants::purple:
		RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, glm::vec3(1, 0, 1));
		break;
	}
}

void Skyroads::CheckPlatformIsOut(std::vector<Platform*>& platformsVector) {
	if (platformsVector[0]->getZ() - platformsVector[0]->getScaleZ() / 2.f >= sphere->getZ() + 0.2f) {
		Platform* aux = platformsVector[0];
		for (int i = 0; i < PlatformConstants::count - 1; i++) {
			platformsVector[i] = platformsVector[i + 1];
		}

		aux->reinitializePlatform(platformsVector);

		platformsVector[PlatformConstants::count - 1] = aux;

		GeneratePlatforms(aux);

		for (int i = 0; i < PlatformConstants::count - 1; i++) {
			GeneratePlatforms(platformsVector[i]);
		}
	}
}

void Skyroads::ApplyPlatformEffectOnSphere(Platform* platform) {
	if (platform->getColor() == ColorConstants::red && !sphere->isInAir() && noRespawnSafeTime > 400) {
		cout << "GAME OVER!" << endl;
		exit(0);
	}

	if (platform->getColor() == ColorConstants::yellow && !sphere->isInAir() && noRespawnSafeTime > 200) {
		currentFuel -= 0.25f;
	}
	else if (platform->getColor() == ColorConstants::green && !sphere->isInAir())
	{
		sphere->setDeformation(true);
		currentFuel += 0.5f;
	}
	else if (platform->getColor() == ColorConstants::orange && !sphere->isInAir() && noRespawnSafeTime > 400) {
		speedActivated = true;
	}

	sphere->setOnPlatform(true);
	if (!sphere->isInAir() && gameOverFall == false) {
		platform->setColor(ColorConstants::purple);
	}
}

void Skyroads::SetFirstPerson() {
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(sphere->getX(), sphere->getY(), 1));
	camera->Update();
}

void Skyroads::SetThirdPerson() {
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 2.f, sphere->getZ() + 1.5f));
	camera->Update();
}
