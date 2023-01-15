#pragma once
#include "Core/Debug/Debug.hpp"
#include "Resources/manager/ResourcesManager.hpp"
#include "LowRenderer/Camera.hpp"

#include "Resources/manager/MeshManager.hpp"
#include "Resources/manager/MaterialManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
	struct AppInitialiser
	{
		const unsigned	int		width;
		const unsigned	int		height;
		const unsigned	int		major;
		const unsigned	int		minor;
		const			char*	name;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
	struct UsefulValue
	{
		float clearColor[4];
		bool isWireFrame;
		bool showDebugAction;
		bool showInspector;
		bool showSceneGraph;
		int lightCount[3];
	};

	class App
	{
	private:
		//variable
		Resources::ResourcesManager resourceManager;
		Resources::MeshManager meshManager;
		Resources::MaterialManager materialManager;


		GLFWwindow* window;
		Inputs inputs;
		MouseData mouseData;



		LowRenderer::Camera editCam;
		Debug::Log	log;
	public:
		//variable
		UsefulValue usefulValue;
		//function
		void Init(AppInitialiser p_init);
		void Update(void);
		void LoadResources();
		void UnLoad();
	private:
		void NewFrame(bool mouseCaptured = true);
		void EndFrame();
		void DrawInterface();
	};
}

