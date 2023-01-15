#include "Core/InputManager.hpp"
void Core::processInput(GLFWwindow* window, Inputs& input)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//----------------------W----------------------//
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		input.w = true;
	else
		input.w = false;
	//----------------------A----------------------//
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		input.a = true;
	else
		input.a = false;
	//----------------------S----------------------//
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		input.s = true;
	else
		input.s = false;
	//----------------------D----------------------//
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		input.d = true;
	else
		input.d = false;
	//----------------------Q----------------------//
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		input.q = true;
	else
		input.q = false;
	//----------------------E----------------------//
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		input.e = true;
	else
		input.e = false;
}