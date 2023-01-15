#pragma once
#include "Core/Maths/Maths.hpp"
#include "LowRenderer/Component.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace LowRenderer
{
	class Light : public Component
	{
	public:
		Maths::sVector::Vector4 diffuseColor;
		Maths::sVector::Vector4 ambientColor;
		Maths::sVector::Vector4 specularColor;
	};

	class DirectionalLight : public Light
	{
	private:
		int id;
	public:
		Maths::sVector::Vector3 direction;
		void DrawInIMGUI();
		void Link(uint32_t shader, const int id);
	};

	class PointLight : public Light
	{
	private:
		int id;
	public:
		Maths::sVector::Vector3 position;
		void DrawInIMGUI();
		void Link(uint32_t shader, const int id);
	};

	class SpotLight : public Light
	{
	private:
		int id;
	public:
		void DrawInIMGUI();
		void Link(uint32_t shader, const int id);
	};

}