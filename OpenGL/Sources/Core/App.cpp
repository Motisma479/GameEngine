#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "Core/App.hpp"
#include "Core/InputManager.hpp"

#include "Resources/Shader.hpp"
#include "Resources/ShaderProgram.hpp"
#include "LowRenderer/Camera.hpp"

#include "Resources/Loader.hpp"

#include "Core/DataStructure/Scene.hpp"

#include <iostream>
#include <cassert>

void Core::App::Init(Core::AppInitialiser p_init) {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_init.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_init.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


	// glfw window creation
	// --------------------
	window = glfwCreateWindow(p_init.width, p_init.height, p_init.name, NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		assert("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, p_init.framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		assert("Failed to initialize GLAD");
	}


	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(p_init.glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glEnable(GL_BLEND);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGui::StyleColorsDark();

	LowRenderer::CameraData cameraData =
	{
		70,
		1000,
		0.1f
	};
	editCam.ChangeData(cameraData);

	//UseFulValue
	usefulValue = {
	{0.2f, 0.3f, 0.3f, 1.0f},
	false,
	false,
	true,
	true,
	{0,0,0}
	};
}
void Core::App::LoadResources()
{
	Loader::loadModel("Resources/Obj/default.obj", &resourceManager, &meshManager, &materialManager);
	Loader::loadModel("Resources/Obj/Triforce.obj", &resourceManager, &meshManager, &materialManager);
	Loader::loadModel("Resources/Obj/SusCube.obj", &resourceManager, &meshManager, &materialManager);


	resourceManager.Create<Resources::FragmentShader>("Resources/Shaders/fragmentShaderSource.glsl");
	resourceManager.Create<Resources::VertexShader>("Resources/Shaders/vertexShaderSource.glsl");
	DEBUG_LOG("Resources loding DONE\n");
}

//Get back Events and setup ImGUI frame
void Core::App::NewFrame(bool mouseCaptured)
{
	glfwPollEvents();
	processInput(window, inputs);
	mouseData.Check(window);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	if (mouseCaptured)
		ImGui::GetIO().MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	ImGui::NewFrame();
	glClearColor(usefulValue.clearColor[0], usefulValue.clearColor[1], usefulValue.clearColor[2], usefulValue.clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//Clear buffer et render ImGUI
void Core::App::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);

}

void Core::App::DrawInterface()
{
	//ImGui::ShowDemoWindow();
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New",nullptr,nullptr,false)) {}
			if (ImGui::MenuItem("Open", "Ctrl+O", nullptr, false)) {}
			if (ImGui::BeginMenu("Open Recent",false))
			{
				ImGui::MenuItem("foo.cpp");
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S", nullptr, false)) {}
			if (ImGui::MenuItem("Save As..", nullptr, nullptr, false)) {}

			ImGui::Separator();
			if (ImGui::BeginMenu("Options"))
			{
				ImGui::ColorEdit4("Clear Color", usefulValue.clearColor);
				ImGui::MenuItem("Other Option");
				ImGui::EndMenu();
			}
			/*
			//IMGUI_DEMO_MARKER("Examples/Menu/Colors");
			if (ImGui::BeginMenu("Colors"))
			{
				float sz = ImGui::GetTextLineHeight();
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
					ImVec2 p = ImGui::GetCursorScreenPos();
					ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
					ImGui::Dummy(ImVec2(sz, sz));
					ImGui::SameLine();
					ImGui::MenuItem(name);
				}
				ImGui::EndMenu();
			}*/
			if (ImGui::MenuItem("Quit", "Alt+F4")) { glfwSetWindowShouldClose(window, true); }
			ImGui::EndMenu();
		}/*
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}*/
		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Debug Action", NULL, &usefulValue.showDebugAction);
			ImGui::MenuItem("Scene Graph", NULL, &usefulValue.showSceneGraph);
			ImGui::MenuItem("Inspector", NULL, &usefulValue.showInspector);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (usefulValue.showDebugAction)
	{
		ImGui::SetNextWindowSize(ImVec2(275, 310), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(5, 20), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Debug Action", &usefulValue.showDebugAction))
		{
			ImGui::End();
			return;
		}
		//show when right click on title bar
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close Debug Action"))
				usefulValue.showDebugAction = false;
			ImGui::EndPopup();
		}
		//the container
		ImGui::TextWrapped("FPS: %.1f",1/ImGui::GetIO().DeltaTime);

		//ImGui::Image((ImTextureID)resourceManager.Get<Resources::Texture>("Resources/Textures/debug.png")->Get(), {64,64});

		ImGui::Checkbox("Draw Wireframe", &usefulValue.isWireFrame);
		
		ImGui::TextWrapped("Camera Position: ");
		float camPos[3] = { editCam.viewPosition.x, editCam.viewPosition.y, editCam.viewPosition.z };
		ImGui::DragFloat3("", camPos, 1.f, -100.f, 100.f);
		editCam.viewPosition.x = camPos[0];
		editCam.viewPosition.y = camPos[1];
		editCam.viewPosition.z = camPos[2];

		ImGui::TextWrapped("Camera Rotation: ");
		float camRot[3] = { editCam.viewRotation.x, editCam.viewRotation.y, editCam.viewRotation.z };
		ImGui::DragFloat3(" ", camRot, 0.01f, -180.f, 180.f);
		editCam.viewRotation.x = camRot[0];
		editCam.viewRotation.y = camRot[1];
		editCam.viewRotation.z = camRot[2];
		
		ImGui::End();
	}
	if (usefulValue.showSceneGraph)
	{
		ImGui::SetNextWindowSize(ImVec2(275, 310), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(5, 335), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Scene Graph", &usefulValue.showSceneGraph))
		{
			ImGui::End();
			return;
		}
		//show when right click on title bar
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close Scene Graph"))
				usefulValue.showSceneGraph = false;
			ImGui::EndPopup();
		}

		//the container

		/*********************\
			work with node
		\*********************/

		ImGui::End();
	}
	if (usefulValue.showInspector)
	{
		ImGui::SetNextWindowSize(ImVec2(275, 310), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(5, 650), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Inspector", &usefulValue.showInspector))
		{
			ImGui::End();
			return;
		}
		//show when right click on title bar
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close Inspector"))
				usefulValue.showInspector = false;
			ImGui::EndPopup();
		}

		//the container
		
		/*********************\
			work with node
		\*********************/

		ImGui::End();
	}
}

void Core::App::Update(void)
{
	Resources::ShaderProgram shProg(
		resourceManager.Get<Resources::VertexShader>("Resources/Shaders/vertexShaderSource.glsl"),
		resourceManager.Get<Resources::FragmentShader>("Resources/Shaders/fragmentShaderSource.glsl")
	);

	DataStructure::Scene nScene;

	while (!glfwWindowShouldClose(window))
	{
		NewFrame(false);

		//-----------------------------------------------------------------------------
		glUseProgram(shProg.getShaderProgram());
		
		editCam.Update(window, mouseData, inputs, shProg.getShaderProgram());


		nScene.Draw(editCam.GetVP(), shProg.getShaderProgram());
		nScene.DrawNode(usefulValue.showInspector, true, meshManager, materialManager);
		nScene.DrawGraph(usefulValue.showInspector, true);


		//-----------------------------------------------------------------------------
		if (usefulValue.isWireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		DrawInterface();

		EndFrame();
	}
}

void Core::App::UnLoad()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}