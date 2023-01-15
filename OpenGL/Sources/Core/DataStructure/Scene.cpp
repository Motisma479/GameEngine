#include "Core/DataStructure/Scene.hpp"
#include "Core/Debug/Debug.hpp"
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

DataStructure::Scene::Scene()
{
}

DataStructure::Scene::~Scene()
{
	for (int i = 0; i < data.size(); i++)
	{
        //data[i]->Delete();
		delete data[i];
	}
}
void DataStructure::Scene::Draw(Maths::sMatrix::Mat4 VP, uint32_t shader)
{
	for (int i = 0; i < data.size(); i++)
	{
		data[i]->Update(VP, shader);
        data[i]->Draw(shader);
	}
    std::vector<LowRenderer::DirectionalLight*> TempDir;
    std::vector<LowRenderer::SpotLight*> TempSpo;
    std::vector<LowRenderer::PointLight*> TempPoi;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i]->GetAllDirectionalLight().size(); j++)
        {
            TempDir.emplace_back(data[i]->GetAllDirectionalLight()[j]);

        }

        for (int j = 0; j < data[i]->GetAllSpotLight().size(); j++)
        {
            TempSpo.emplace_back(data[i]->GetAllSpotLight()[j]);

        }

        for (int j = 0; j < data[i]->GetAllPointLight().size(); j++)
        {
            TempPoi.emplace_back(data[i]->GetAllPointLight()[j]);

        }
        

    }
    if(TempDir.size()!=0)
    for (int i = 0; i<TempDir.size() && i < 16; i++)
        TempDir[i]->Link(shader, i);

    if (TempSpo.size() != 0)
        for (int i = 0; i < TempSpo.size() && i < 16; i++)
            TempSpo[i]->Link(shader, i);

    if (TempPoi.size() != 0)
        for (int i = 0; i < TempPoi.size() && i < 16; i++)
            TempPoi[i]->Link(shader, i);

    
}

void DataStructure::Scene::DrawNode(bool& windowExist, const bool& active, Resources::MeshManager& meshManager, Resources::MaterialManager& materialManager)
{
    if(data.size() > 0)
	    data[selected]->DrawInspector(windowExist, active, meshManager, materialManager);
}
void DataStructure::Scene::DrawGraph(bool& windowExist, const bool& active)
{
	if (windowExist && active)
	{
		if (!ImGui::Begin("Scene Graph", &windowExist))
		{
			ImGui::End();
			return;
		}
		//show when right click on title bar
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close Scene Graph"))
				windowExist = false;
			ImGui::EndPopup();
		}

		//the container

        if (ImGui::CollapsingHeader("Scene :"))
        {
            for (int i = 0; i < data.size(); i++)
            {
                //if (ImGui::TreeNode(std::to_string(i).c_str(), data[i]->name))

                if (ImGui::TreeNodeEx(std::to_string(i).c_str(),0, data[i]->name))
                {
                    if (ImGui::IsItemClicked())
                    {
                        selected = i;
                    }
                    /*
                    if (ImGui::Button("Set Material"))
                        ImGui::OpenPopup("Material");
                    if (ImGui::BeginPopup("Material"))
                    {
                        for (int j = 0; j < materialManager.length(); j++)
                        {
                            if (materialManager.GetData(j)->TextureRef != nullptr)
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
                    }*/
                    if (ImGui::Button("Delete"))
                    {
                        data.erase(data.begin() + i);
                    }
                    ImGui::TreePop();
                }
            }


            if (ImGui::Button("Add Node +"))
                ImGui::OpenPopup("NewNode");
            if (ImGui::BeginPopup("NewNode"))
            {
                static char temp[64] = "";
                ImGui::InputText("Node Name", temp, 64);
                if (ImGui::Button("Ok"))
                {
                    DataStructure::Node* newNode = new DataStructure::Node(temp);
                    data.emplace_back(newNode);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

        }
        ImGui::End();
	}
}