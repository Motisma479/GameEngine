#pragma once
#include "Resources/IResource.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Resources
{
	class Texture : public IResources
	{
	private:
		int d_width, d_height, nrChannels;
		GLuint sampler;
		GLuint texture;
		int index;
	public:
		void Create(const char* name);
		void Delete();
		void Link(uint32_t shader);
		GLuint Get();
		int width();
		int height();
		Texture();
	};
}