#pragma once
#include "Resources/Shader.hpp"

namespace Resources
{
	class ShaderProgram
	{
	private:
		uint32_t d_ShaderProgram;
	public:
		ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader);
		uint32_t getShaderProgram();
	};
}