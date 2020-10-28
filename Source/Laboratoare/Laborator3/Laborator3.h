#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#define SQUARE_SIDE				100
#define TRANSLATION_FACTOR		100
#define ROTATION_FACTOR			0.25
#define SCALING_FACTOR			0.5
#define ORBITING_DISTANCE		125

class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void RenderSquare1UpAndDown(float deltaTimeSeconds);
		void RenderSquare2Spin(float deltaTimeSeconds);
		void RenderSquare3PulseSize(float deltaTimeSeconds);
		void RenderSquare4Orbit(float deltaTimeSeconds);

	protected:
		glm::mat3 modelMatrix;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		bool limitTranslation;
		bool limitScaling;
};
