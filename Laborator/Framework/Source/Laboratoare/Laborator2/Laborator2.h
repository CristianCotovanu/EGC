#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#define CIRCLE_RADIUS	 1.5
#define LINES_COUNT		 25
#define DEGREES_360		 360
#define DEGREES_180		 180
#define PI				 3.14159265358979323846

class Laborator2 : public SimpleScene
{
	public:
		Laborator2();
		~Laborator2();

		void Init() override;

	private:
		Mesh* CreateMesh(const char *name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

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

		void UpdateCullPerspective();

	protected:
		GLenum cullFace;
		GLenum polygonMode;
};
