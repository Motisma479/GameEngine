#include "LowRenderer/Camera.hpp"
#include "Core/Debug/Debug.hpp"

#define MOUSESPEED 0.25f
#define CAMERASPEED 0.25f

void LowRenderer::Camera::SetProjection()
{
	float view = tanf((data.fov/2.0f) * (float)DEG2RAD);
	
	float projectionMatrixValue[16] =
	{
		1/(aspectRatio * view) , 0, 0, 0,
		0, 1/view, 0, 0,
		0, 0, -(data.far + data.near)/ (data.far - data.near), -(2* data.far * data.near) / (data.far - data.near),
		0, 0, -1, 0
	};
	projectionMatrix = projectionMatrixValue;
}
void LowRenderer::Camera::SetViewMatrix()
{
	Maths::sVector::Vector3 xaxis = { cos(viewRotation.y * DEG2RAD), 0, -sin(viewRotation.y * DEG2RAD) };
	Maths::sVector::Vector3 yaxis = { sin(viewRotation.y * DEG2RAD) * sin(viewRotation.x * DEG2RAD), cos(viewRotation.x * DEG2RAD), cos(viewRotation.y * DEG2RAD) * sin(viewRotation.x * DEG2RAD) };
	Maths::sVector::Vector3 zaxis = { sin(viewRotation.y * DEG2RAD) * cos(viewRotation.x * DEG2RAD), -sin(viewRotation.x * DEG2RAD), cos(viewRotation.x * DEG2RAD) * cos(viewRotation.y * DEG2RAD) };

	float viewXaxis = (xaxis.x * viewPosition.x + xaxis.y * viewPosition.y + xaxis.z * viewPosition.z);
	float viewYaxis = (yaxis.x * viewPosition.x + yaxis.y * viewPosition.y + yaxis.z * viewPosition.z);
	float viewZaxis = (zaxis.x * viewPosition.x + zaxis.y * viewPosition.y + zaxis.z * viewPosition.z);

	float viewMatrixValue[16] =
	{
		xaxis.x, xaxis.y, xaxis.z, - viewXaxis,
		yaxis.x, yaxis.y, yaxis.z, - viewYaxis,
		zaxis.x, zaxis.y, zaxis.z, - viewZaxis,
		0, 0, 0, 1
	};
	viewMatrix = viewMatrixValue;
}

LowRenderer::Camera::Camera() : data({
		90,
		1,
		100
	}), aspectRatio(1)
{

}
LowRenderer::Camera::Camera(const CameraData p_newData) : data(p_newData), aspectRatio(1)
{

}

void LowRenderer::Camera::Update(GLFWwindow* window, MouseData& data, Inputs& inputs, uint32_t shader)
{
	if (data.isCaptured)
	{
		
		Maths::sVector::Vector4 mouvement;

		if (inputs.w)
			mouvement.z += -1;

		if (inputs.s)
			mouvement.z += 1;

		if (inputs.a)
			mouvement.x += -1;

		if (inputs.d)
			mouvement.x += 1;
		if (inputs.q)
			mouvement.y += 1;
		if (inputs.e)
			mouvement.y += -1;
		

		mouvement *= CAMERASPEED;

		viewRotation += Maths::sVector::Vector3{ -(float)data.mouseDeltaY, -(float)data.mouseDeltaX, 0 } *MOUSESPEED;
		if (viewRotation.y > 180)
			viewRotation.y = -180;
		if (viewRotation.y < -180)
			viewRotation.y = 180;

		if (viewRotation.x > 90)
			viewRotation.x = 90;
		if (viewRotation.x < -90)
			viewRotation.x = -90;

		mouvement *= (Maths::sMatrix::Mat4::CreateYRotationMatrix(-viewRotation.y * DEG2RAD));
		viewPosition += mouvement;
		//viewPosition.z = viewPosition.z + sinf(viewRotation.x * PI_NUM / 180.f) * mVel.z + cosf(viewRotation.x * PI_NUM / 180.f) * mVel.x;

	}

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	aspectRatio = (float)width / (float)height;

	SetProjection();
	SetViewMatrix();
	VP = (projectionMatrix * viewMatrix);

	glUniform3f(glGetUniformLocation(shader, "viewPos"), viewPosition.x, viewPosition.y, viewPosition.z);
}
void LowRenderer::Camera::ChangeData(const CameraData p_newData)
{
	data = p_newData;
}
Maths::sMatrix::Mat4 LowRenderer::Camera::GetVP()
{
	return VP;
}