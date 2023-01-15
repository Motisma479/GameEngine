#include "Resources/Material.hpp"
#include "Core/Debug/Debug.hpp"

Resources::Material::Material() :
	ambient({ 0, 0, 0 }),
	diffuse({ 0, 0, 0 }),
	specular({ 0, 0, 0 }),
	emisive({ 0, 0, 0 }),
	shininess(0)
{

}

void Resources::Material::Create(const char* name)
{
	ASSERT(true);
}
void Resources::Material::Delete()
{

}
void Resources::Material::Link(uint32_t shader) 
{
	glUniform3f(glGetUniformLocation(shader, "material.ambient"), ambient.x, ambient.y, ambient.z); // set it manually
	glUniform3f(glGetUniformLocation(shader, "material.diffuse"), diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(glGetUniformLocation(shader, "material.specular"), specular.x, specular.y, specular.z);
	glUniform3f(glGetUniformLocation(shader, "material.emisive"), emisive.x, emisive.y, emisive.z);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"), shininess);
}