#pragma once
#include"Resources/IResource.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Resources
{
	class Shader : public IResources
	{
	private:
		uint32_t d_Shader;
	protected:
		GLenum ShaderParam;
		const char* ErrorInfo;
	public:
		void Create(const char* name);
		int GetShader();
		void Delete();
		Shader(void);
	};
	class VertexShader : public Shader
	{
	public:
		VertexShader();
	};
	class FragmentShader : public Shader
	{
	public:
		FragmentShader();
	};
}