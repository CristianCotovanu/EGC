#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <Laboratoare\Skyroads\Entities\Sphere\Sphere.h>
#include <Laboratoare\Skyroads\Entities\Platform\Platform.h>

class Skyroads : public SimpleScene
{
public:
	Skyroads();
	~Skyroads();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
	void RenderCustomMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void GeneratePlatforms(Platform* platform);
	void CheckPlatformIsOut(std::vector<Platform*>& platformsVector);
	void ApplyPlatformEffectOnSphere(Platform* platform);
	void SetFirstPerson();
	void SetThirdPerson();

	Sphere* sphere;
	std::vector<Platform*> platformsLeft;
	std::vector<Platform*> platformsCenter;
	std::vector<Platform*> platformsRight;

	GLint crtPlatformNumber;
	GLfloat platformsSpeed;
	GLboolean speedActivated;

	GLfloat lastPlatformLeftZ;
	GLfloat lastPlatformRightZ;
	GLfloat lastPlatformCenterZ;
	GLfloat lastPlatformLeftScaleZ;
	GLfloat lastPlatformRightScaleZ;
	GLfloat lastPlatformCenterScaleZ;

	GLboolean isWPressed;
	GLboolean isSPressed;
	GLboolean isSpacePressed;

	GLfloat currentFuel;
	GLfloat fuelBarNewPosition;
	GLfloat stepFuelBar;

	GLboolean gameOverFall;
	GLfloat time;
	GLfloat noRespawnSafeTime;
	GLint cameraType;
};