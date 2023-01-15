#include "Resources/Shader.hpp"
#include "Core/Debug/Debug.hpp"

#include <fstream>

Resources::Shader::Shader(void)
{

}
void Resources::Shader::Create(const char* name)
{
	std::ifstream shader(name, std::ios::in | std::ios::binary | std::ios::ate);
	if (!shader.is_open()) {
		DEBUG_LOG("Could not open the file - ' %s %s", name, "'\n");
	}
	size_t size = shader.tellg();
	shader.seekg(0);
	char* file = new char[size + 1];
	shader.read(file, size);
	shader.close();
	file[size] = 0; // Set the last char of the file to 0

	d_Shader = glCreateShader(ShaderParam);
	glShaderSource(d_Shader, 1, &file, NULL);
	glCompileShader(d_Shader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(d_Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(d_Shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< ErrorInfo <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

int Resources::Shader::GetShader()
{
	return d_Shader;
}

void Resources::Shader::Delete()
{
	glDeleteShader(d_Shader);
}

Resources::FragmentShader::FragmentShader()
{
	ShaderParam = GL_FRAGMENT_SHADER;
	ErrorInfo = "FRAGMENT";
}

Resources::VertexShader::VertexShader()
{
	ShaderParam = GL_VERTEX_SHADER;
	ErrorInfo = "VERTEX";
}