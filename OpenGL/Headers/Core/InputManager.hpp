#pragma once
#include "App.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Core
{
	void processInput(GLFWwindow* window, Inputs &input);
}