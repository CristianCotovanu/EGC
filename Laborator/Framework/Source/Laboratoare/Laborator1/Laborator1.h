#pragma once

#include <Component/SimpleScene.h>

#define EXTRA_OBJECTS	3

class Laborator1 : public SimpleScene
{
	private:
		float redFactor;
		float greenFactor;
		float blueFactor;
		bool colorReset = true;

		float objX;
		float objY;
		float objZ;
		float objScale;
		std::string objName;
		int objIdx;

	public:
		Laborator1();
		~Laborator1();

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

		void UpdateClearColour();
		void UpdateRenderedObject();
};
