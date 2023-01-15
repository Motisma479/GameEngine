#include "LowRenderer/Model.hpp"

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "Core/Debug/Debug.hpp"

LowRenderer::Model::Model()
{}
LowRenderer::Model::~Model()
{}
void LowRenderer::Model::Draw(uint32_t& shader)
{
    for (int i = 0; i < material.size(); i++)
    {
        if (material[i]->TextureRef != nullptr)
            material[i]->TextureRef->Link(shader);
        material[i]->Link(shader);
    }
    for (int i = 0; i < mesh.size(); i++)
    {
        mesh[i]->Draw();
    }
}
void LowRenderer::Model::DrawInIMGUI(Resources::MeshManager& meshManager, Resources::MaterialManager& materialManager)
{
	if (ImGui::CollapsingHeader("Model :"))
	{
        for (int i = 0; i < mesh.size(); i++)
        {
            if (ImGui::TreeNode((std::string("Mesh: ") += std::to_string(i)).c_str()))
            {
                ImGui::TextWrapped("Material set: ");
                if(material.size() > 0)
                {
                    if (material[i]->TextureRef != nullptr)
                        ImGui::Image((ImTextureID)material[i]->TextureRef->Get(), ImVec2(material[i]->TextureRef->width(), material[i]->TextureRef->height()), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
                    ImGui::TextWrapped(material[i]->name.c_str());
                }

                if (ImGui::Button("Set Material"))
                    ImGui::OpenPopup("Material");
                if (ImGui::BeginPopup("Material"))
                {
                    for (int j = 0; j < materialManager.length(); j++)
                    {
                        if(materialManager.GetData(j)->TextureRef != nullptr)
                            ImGui::Image((ImTextureID)materialManager.GetData(j)->TextureRef->Get(), ImVec2(materialManager.GetData(j)->TextureRef->width(), materialManager.GetData(j)->TextureRef->height()), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
                        if (ImGui::Button(materialManager.GetData(j)->name.c_str()))
                        {
                            if (material.size() < mesh.size())
                                material.push_back(materialManager.GetData(j));
                            else
                                material[i] = materialManager.GetData(j);
                            ImGui::CloseCurrentPopup();
                        }
                    }
                    ImGui::Separator();
                    ImGui::Text("Tooltip here");
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("I am a tooltip over a popup");


                    ImGui::EndPopup();
                }
                if (ImGui::Button("Delete"))
                {
                    mesh.erase(mesh.begin() + i);
                }
                ImGui::TreePop();
            }
        }


        if (ImGui::Button("Add Mesh +"))
            ImGui::OpenPopup("Meshs");
        if (ImGui::BeginPopup("Meshs"))
        {
            for(int i = 0; i < meshManager.length(); i++)
            {
                if (ImGui::Button(meshManager.GetData(i)->name.c_str()))
                {
                    mesh.push_back(meshManager.GetData(i));
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::Separator();
            ImGui::Text("Tooltip here");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("I am a tooltip over a popup");

            
            ImGui::EndPopup();
        }
	}
}