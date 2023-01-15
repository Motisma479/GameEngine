#include "LowRenderer/Light.hpp"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

void LowRenderer::DirectionalLight::DrawInIMGUI()
{
	if (ImGui::CollapsingHeader("Directional Light :"))
	{
		ImGui::ColorEdit3("diffuse Color", diffuseColor.ToFloat4());
		ImGui::ColorEdit3("ambient Color", ambientColor.ToFloat4());
		ImGui::ColorEdit3("specular Color", specularColor.ToFloat4());
		ImGui::DragFloat3("direction", direction.ToFloat3(), 0.1f);
	}
}
void LowRenderer::DirectionalLight::Link(uint32_t shader, const int id)
{
	glUniform3f(glGetUniformLocation(shader, (std::string("dirLight[") += std::to_string(id) += "].p_direction").c_str()), direction.x, direction.y, direction.z); // set it manually
	glUniform3f(glGetUniformLocation(shader, (std::string("dirLight[") += std::to_string(id) += "].p_ambientColor").c_str()), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shader, (std::string("dirLight[") += std::to_string(id) += "].p_diffuseColor").c_str()), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shader, (std::string("dirLight[") += std::to_string(id) += "].p_specularColor").c_str()), specularColor.x, specularColor.y, specularColor.z);
}
void LowRenderer::PointLight::DrawInIMGUI(){}
void LowRenderer::PointLight::Link(uint32_t shader, const int id) {}
void LowRenderer::SpotLight::DrawInIMGUI(){}
void LowRenderer::SpotLight::Link(uint32_t shader, const int id) {}