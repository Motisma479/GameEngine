#include "Core/DataStructure/Node.hpp"
#include "Core/Debug/Debug.hpp"

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

DataStructure::Node::Node() :
	name("Sheesh"),
	transform({
		{0,0,0},
		{0,0,0},
		{1,1,1}
	})
{

}
DataStructure::Node::Node(const char* newName) :
	transform({
		{0,0,0},
		{0,0,0},
		{1,1,1}
		})
{
	for (int i = 0; i < newName[i] != 0; i++)
		name[i] = newName[i];
}
DataStructure::Node::~Node()
{
	for(int i = (int)component.size()-1; i > 0; i--)
	{
		delete component[i];
	}
	component.clear();
}

void DataStructure::Node::DrawInspector(bool& windowExist, const bool& active, Resources::MeshManager& meshManager, Resources::MaterialManager& materialManager)
{
	if (windowExist && active)
	{
		if (!ImGui::Begin("Inspector", &windowExist))
		{
			ImGui::End();
			return;
		}
		//Your implementation here

		ImGui::InputText("Input", name, IM_ARRAYSIZE(name));
		ImGui::TextWrapped(name);
		if (ImGui::CollapsingHeader("Transform :"))
		{
			ImGui::DragFloat3("position", transform.position.ToFloat3(), 0.1f);
			ImGui::DragFloat3("rotation", transform.rotation.ToFloat3(), 0.1f);
			ImGui::DragFloat3("scale", transform.scale.ToFloat3(), 0.1f);
		}

		for (int i = 0; i < component.size(); i++)
		{
			if (auto model = dynamic_cast<LowRenderer::Model*>(component[i]))
			{ 
				model->DrawInIMGUI(meshManager, materialManager);
			}
			else
				component[i]->DrawInIMGUI();
		}

		if(ImGui::Button("New component +"))
			ImGui::OpenPopup("component");
		if (ImGui::BeginPopup("component"))
		{
			if (ImGui::Button("Add Model"))
			{
				AddComponent<LowRenderer::Model>();
				ImGui::CloseCurrentPopup();
			}

			
				if (ImGui::Button("Add Directional Light"))
				{
					AddComponent<LowRenderer::DirectionalLight>();
					ImGui::CloseCurrentPopup();
				}
			
				if (ImGui::Button("Add Point Light"))
				{
					ImGui::CloseCurrentPopup();
				}
			
				if (ImGui::Button("Add Spot Light"))
				{
					ImGui::CloseCurrentPopup();
				}
		
			ImGui::EndPopup();
		}
		
		//------------------------
		ImGui::End();
	}

	
}
void DataStructure::Node::Update(Maths::sMatrix::Mat4 VP, uint32_t shader)
{
	modelMatrix = Maths::sMatrix::Mat4::CreateTransformMatrix(transform.position, transform.rotation, transform.scale);
	MVP = VP * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, MVP.GetData());
	glUniformMatrix4fv(glGetUniformLocation(shader, "M"), 1, GL_FALSE, modelMatrix.GetData());

}

void DataStructure::Node::Draw(uint32_t shader) 
{
	for (int i = 0; i < component.size(); i++)
	{
		if (auto model = dynamic_cast<LowRenderer::Model*>(component[i]))
		{
			model->Draw(shader);
		}
		else
			component[i]->Draw();
	}
}