#include "Utils.hpp"
#include "Core/Debug/Debug.hpp"
void MouseData::Check(GLFWwindow* window)
{
	static bool checkFirst = true;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		isCaptured = true;

		if (checkFirst)
		{
			glfwGetCursorPos(window, &mouseX, &mouseY);
			checkFirst = false;
		}

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		
		double newMouseX, newMouseY;
		glfwGetCursorPos(window, &newMouseX, &newMouseY);
		mouseDeltaX = (float)(newMouseX - mouseX);
		mouseDeltaY = (float)(newMouseY - mouseY);
		mouseX = newMouseX;
		mouseY = newMouseY;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		isCaptured = false;
		checkFirst = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}