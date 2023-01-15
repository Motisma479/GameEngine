#include "Resources/Texture.hpp"
#include "Core/Debug/Debug.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

Resources::Texture::Texture()
{

}
void Resources::Texture::Create(const char* name)
{

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(name, &d_width, &d_height, &nrChannels, 4);
	DEBUG_LOG("Width: %d, Height: %d", d_width, d_height)

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d_width, d_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//replace to NEAREST
	//glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

	printf("\n\n%d\n\n", texture);

	glBindTextureUnit(texture, texture);
	glBindSampler(texture, sampler);
	
	DEBUG_LOG("Texture created\n");
}
void Resources::Texture::Link(uint32_t shader)
{
	glUniform1i(glGetUniformLocation(shader, "texture1"), texture); // set it manually
}
GLuint Resources::Texture::Get()
{
	return texture;
}
int Resources::Texture::width()
{
	return d_width;
}
int Resources::Texture::height()
{
	return d_height;
}
void Resources::Texture::Delete()
{
	glDeleteTextures(1, &texture);
	glDeleteSamplers(1, &sampler);
}