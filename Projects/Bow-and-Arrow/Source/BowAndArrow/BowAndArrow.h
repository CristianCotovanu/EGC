#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <Core/Engine.h>
#include <BowAndArrow\Entities\Shuriken.h>
#include <BowAndArrow\Entities\Balloon.h>
#include <BowAndArrow\Entities\Bow.h>
#include <BowAndArrow\Entities\Arrow.h>
#include <BowAndArrow\Entities\HealthIndicator.h>

class BowAndArrow : public SimpleScene
{
	public:
		BowAndArrow();
		~BowAndArrow();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(GLfloat deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(GLfloat deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void RenderHealthIndicators();
		void RenderBowAndChargingMeter();
		void RenderArrow();
		void RenderBalloons(float deltaTimeSeconds);
		void RenderShurikens(float deltaTimeSeconds);

	public:
		glm::mat3 modelMatrix;
		Arrow* arrow;
		Bow* bow;
		std::vector<Shuriken*> shurikens;
		std::vector<Balloon*> balloons;
		std::vector<HealthIndicator*> healthIndicators;
		GLfloat score;
		GLfloat movingMouseRadians;
		GLfloat arrowRadians;
		GLfloat scaleChargingMeterX, scaleChargingMeterY;
};
