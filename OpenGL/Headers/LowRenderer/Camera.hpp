#pragma once
#include "Core/Maths/Maths.hpp"
#include "Utils.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LowRenderer
{
	struct CameraData
	{
		float fov;
		float far;
		float near;
	};
	class Camera
	{
	private:
		CameraData data;

		Maths::sMatrix::Mat4 projectionMatrix;
		Maths::sMatrix::Mat4 viewMatrix;
		Maths::sMatrix::Mat4 VP;

		float aspectRatio;

		void SetProjection();
		void SetViewMatrix();
	public:
		Camera();
		Camera(const CameraData p_newData);
		Maths::sVector::Vector3 viewPosition;
		Maths::sVector::Vector3 viewRotation;
		void Update(GLFWwindow* window, MouseData& data, Inputs& inputs, uint32_t shader);
		void ChangeData(const CameraData p_newData);
		
		Maths::sMatrix::Mat4 GetVP();
	};
}