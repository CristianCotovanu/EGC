#include "BowAndArrow.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Helpers/DrawFigure.h"
#include <BowAndArrow/Helpers/Transform2D.h>
#include <BowAndArrow/Helpers/CollisionManager.h>
#include <BowAndArrow/Constants/Constants.cpp>

using namespace std;

BowAndArrow::BowAndArrow() { }

BowAndArrow::~BowAndArrow() { }

void BowAndArrow::Init()
{
	auto resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	bow = new Bow((float)5, (float)(resolution.y / 2), BowConstants::radius);
	arrow = new Arrow(bow->getX(), bow->getY(), ArrowConstants::width, ArrowConstants::height);

	for (int i = 0; i < GeneralConstants::maxHealth; i++) {
		healthIndicators.push_back(new HealthIndicator(15 + i * 25, resolution.y - 25, 50));
	}

	for (int i = 0; i < ShurikenConstants::count; i++) {
		shurikens.push_back(new Shuriken(
			rand() % resolution.x, 
			rand() % resolution.y - resolution.y, 
			ShurikenConstants::width * sqrt(2)));
	}

	for (int i = 0; i < BalloonConstants::yellowCount; i++) {
		balloons.push_back(new Balloon(
			rand() % resolution.x + BalloonConstants::safetyMargin, 
			rand() % resolution.y - resolution.y, 
			BalloonConstants::radius, 
			true));
	}

	for (int i = 0; i < BalloonConstants::redCount; i++) {
		balloons.push_back(new Balloon(
			rand() % resolution.x + BalloonConstants::safetyMargin, 
			rand() % resolution.y - resolution.y, 
			BalloonConstants::radius, 
			false));
	}

	arrowRadians = 0;
	movingMouseRadians = 0;
	scaleChargingMeterX = GeneralConstants::chargingMeterLength;
	scaleChargingMeterY = GeneralConstants::chargingMeterWidth;

	Mesh* arrow = DrawFigure::CreateArrow("arrow", ArrowConstants::height, ArrowConstants::width, glm::vec3(0, 0, 0), 1);
	Mesh* bow = DrawFigure::CreateBow("bow", BowConstants::radius, glm::vec3(0.4f, 0.2f, 0));
	Mesh* chargingMeter = DrawFigure::CreateRectangle("chargingMeter", glm::vec3(1.f, 1.f, 1.f), 
		GeneralConstants::chargingMeterLength, GeneralConstants::chargingMeterWidth, glm::vec3(1.f, 0, 0), 1);
	Mesh* healthCircle = DrawFigure::CreateCircle("healthCircle", GeneralConstants::healthIndicatorRadius, glm::vec3(1.f, 0, 0));
	Mesh* redBalloon = DrawFigure::CreateBalloon("redBalloon", BalloonConstants::radius, glm::vec3(1.f, 0, 0));
	Mesh* yellowBalloon = DrawFigure::CreateBalloon("yellowBalloon", BalloonConstants::radius, glm::vec3(1.f, 1.f, 0));
	Mesh* thread = DrawFigure::CreateBalloonThread("thread", 3, 30, glm::vec3(0, 0, 0));
	Mesh* shuriken = DrawFigure::CreateShuriken("shuriken", ShurikenConstants::width, ShurikenConstants::width, 2 * ShurikenConstants::width, glm::vec3(0, 0, 0));

	AddMeshToList(arrow);
	AddMeshToList(bow);
	AddMeshToList(chargingMeter);
	AddMeshToList(healthCircle);
	AddMeshToList(redBalloon);
	AddMeshToList(yellowBalloon);
	AddMeshToList(thread);
	AddMeshToList(shuriken);
}

void BowAndArrow::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	auto resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void BowAndArrow::Update(float deltaTimeSeconds)
{
	RenderHealthIndicators();
	RenderBowAndChargingMeter();
	RenderArrow();
	RenderBalloons(deltaTimeSeconds);
	RenderShurikens(deltaTimeSeconds);
}

void BowAndArrow::RenderHealthIndicators() {
	for (auto& healthCircle : healthIndicators) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(healthCircle->getX(), healthCircle->getY());
		RenderMesh2D(meshes["healthCircle"], shaders["VertexColor"], modelMatrix);
	}
}

void BowAndArrow::RenderBowAndChargingMeter() {
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(bow->getX(), bow->getY());
	modelMatrix *= Transform2D::Rotate(movingMouseRadians);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(bow->getX(), bow->getY() - bow->getRadius() * 4 / 3);
	modelMatrix *= Transform2D::Scale(scaleChargingMeterX, scaleChargingMeterY);
	RenderMesh2D(meshes["chargingMeter"], shaders["VertexColor"], modelMatrix);
}

void BowAndArrow::RenderArrow() {
	auto resolution = window->GetResolution();

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(arrow->getX(), arrow->getY());
	modelMatrix *= Transform2D::Rotate(!arrow->isMoving() ? movingMouseRadians : arrowRadians);
	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

	if (arrow->isMoving() && arrow->getX() < resolution.x) {
		arrow->setX(arrow->getX() + arrow->getChargeMeter() * cos(arrowRadians));
		arrow->setY(arrow->getY() + arrow->getChargeMeter() * sin(arrowRadians));
	}

	if (arrow->isMoving() && (arrow->getX() >= resolution.x
							|| arrow->getY() >= resolution.y
							|| arrow->getY() <= 0))
	{
		arrow->setX(bow->getX());
		arrow->setY(bow->getY());
		arrow->resetChargeMeter();
		arrow->setMoving(false);
	}
}

void BowAndArrow::RenderBalloons(float deltaTimeSeconds) {
	auto resolution = window->GetResolution();

	for (auto& balloon : balloons) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(1, balloon->getScaleY());
		modelMatrix *= Transform2D::Translate(balloon->getX(), balloon->getY());

		if (balloon->isPopped() && balloon->getY() <= 0) {
			balloon->respawn(resolution.x, resolution.y);
		}
		else 
		{
			if (balloon->isEvil())
				RenderMesh2D(meshes["yellowBalloon"], shaders["VertexColor"], modelMatrix);
			else
				RenderMesh2D(meshes["redBalloon"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Scale(1, balloon->getScaleY());
			modelMatrix *= Transform2D::Translate(balloon->getX(), balloon->getY() - 2 * balloon->getRadius());
			RenderMesh2D(meshes["thread"], shaders["VertexColor"], modelMatrix);

			if (balloon->getY() >= resolution.y)
				balloon->respawn(resolution.x, resolution.y);
			else
				balloon->setY(balloon->getY() + balloon->getSpeed() * deltaTimeSeconds);
		}
	}

	for (auto& balloon : balloons) {
		if (!balloon->isPopped() && CollisionManager::CollideArrowBalloon(arrow, balloon)) {
			balloon->isEvil() ? --score : ++score;
			balloon->pop();
			cout << "Score: " << score << endl;
		}
	}
}

void BowAndArrow::RenderShurikens(float deltaTimeSeconds) {
	auto resolution = window->GetResolution();

	for (auto& shuriken : shurikens) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(shuriken->getX(), shuriken->getY());
		modelMatrix *= Transform2D::Translate(ShurikenConstants::width, ShurikenConstants::width);
		modelMatrix *= Transform2D::Rotate(shuriken->getRotationStep());
		modelMatrix *= Transform2D::Translate(-ShurikenConstants::width, -ShurikenConstants::width);
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

		shuriken->setRotationStep(shuriken->getRotationStep() + deltaTimeSeconds * ShurikenConstants::rotationFactor);

		if (shuriken->getX() <= 0)
			shuriken->respawn(resolution.x, resolution.y);
		else
			shuriken->setX(shuriken->getX() - ShurikenConstants::speed * deltaTimeSeconds);

		if (CollisionManager::CollideBowShuriken(bow, shuriken)) {
			if (!healthIndicators.empty()) {
				healthIndicators.erase(healthIndicators.end() - 1);
			}
			else
			{
				cout << "Game over!" << endl;
				cout << "Your final score is: " << score << " !" << endl;
				exit(-1);
			}
			shuriken->respawn(resolution.x, resolution.y);
		}

		if (CollisionManager::CollideArrowShuriken(arrow, shuriken)) {
			cout << "Score: " << ++score << endl;
			shuriken->respawn(resolution.x, resolution.y);
		}
	}
}

void BowAndArrow::FrameEnd()
{

}

void BowAndArrow::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_1))
	{
		if (!arrow->isMoving() && arrow->getChargeMeter() < ArrowConstants::chargingLimit)
		{
			arrow->setChargeMeter(arrow->getChargeMeter() + deltaTime * ArrowConstants::chargingFactor);
			scaleChargingMeterX += deltaTime * ArrowConstants::chargingFactor / 2;
		}
	}

	if (window->KeyHold(GLFW_KEY_W))
	{
		if (bow->getY() <= window->GetResolution().y - BowConstants::radius)
		{
			bow->setY(bow->getY() + deltaTime * BowConstants::movementFactor);
			if (!arrow->isMoving())
			{
				arrow->setY(arrow->getY() + deltaTime * BowConstants::movementFactor);
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (bow->getY() >= 0 + BowConstants::radius) {
			bow->setY(bow->getY() - deltaTime * BowConstants::movementFactor);
			if (!arrow->isMoving()) {
				arrow->setY(arrow->getY() - deltaTime * BowConstants::movementFactor);
			}
		}
	}
}

void BowAndArrow::OnKeyPress(int key, int mods) { }

void BowAndArrow::OnKeyRelease(int key, int mods) { }

void BowAndArrow::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	auto resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
	GLfloat d1 = mouseX - bow->getX();
	GLfloat d2 = resolution.y - mouseY - bow->getY();
	movingMouseRadians = glm::atan((float)d2, (float)d1);
}

void BowAndArrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void BowAndArrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	arrowRadians = !arrow->isMoving() ? movingMouseRadians : arrowRadians;
	arrow->setMoving(true);
	scaleChargingMeterX = GeneralConstants::chargingMeterLength;
}

void BowAndArrow::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void BowAndArrow::OnWindowResize(int width, int height)
{
}
