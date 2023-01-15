#include "Resources/ShaderProgram.hpp"
#include "Core/Debug/Debug.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Resources::ShaderProgram::ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader)
{
	int success;
	char infoLog[512];

	d_ShaderProgram = glCreateProgram();
	glAttachShader(d_ShaderProgram, vertexShader->GetShader());
	glAttachShader(d_ShaderProgram, fragmentShader->GetShader());
	glLinkProgram(d_ShaderProgram);
	// check for linking errors
	glGetProgramiv(d_ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(d_ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

}
uint32_t Resources::ShaderProgram::getShaderProgram()
{
	return d_ShaderProgram;
}