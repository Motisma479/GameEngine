#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
struct MouseData
{
	bool isCaptured;
	double mouseX = 0.0;
	double mouseY = 0.0;
	float mouseDeltaX = 0.0;
	float mouseDeltaY = 0.0;
	void Check(GLFWwindow* window);
};
struct Inputs
{
	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
	bool q = false;
	bool e = false;
};