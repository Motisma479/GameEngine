#pragma once
#include "Core/Maths/Maths.hpp"

#include "LowRenderer/Model.hpp"
#include "LowRenderer/Light.hpp"

//#include "Resources/Texture.hpp"
namespace DataStructure
{
	struct Transform
	{
		Maths::sVector::Vector3 position;
		Maths::sVector::Vector3 rotation;
		Maths::sVector::Vector3 scale;
	};
	
	class Node
	{
	private:
		Transform transform;

		std::vector<LowRenderer::Component*> component;

		//TR mesh;
		Maths::sMatrix::Mat4 MVP;
		Maths::sMatrix::Mat4 modelMatrix;

		template <typename T>
		void AddComponent()
		{
			T* temp = new T;
			component.push_back((LowRenderer::Component*)temp);
		}
	public:
		char name[64];
		Node();
		Node(const char* newName);
		~Node();
		void DrawInspector(bool& windowExist, const bool& active, Resources::MeshManager& meshManager, Resources::MaterialManager& materialManager);
		void Update(Maths::sMatrix::Mat4 VP, uint32_t shader);
		//Node(const Maths::sVector::Vector3 p_Position, const Maths::sVector::Vector3 p_Rotation, const Maths::sVector::Vector3 p_Scale, Resources::Model* p_Models, Resources::Texture* p_Texture);
		//void Update(Maths::sMatrix::Mat4 VP, uint32_t shader);

		
		std::vector<LowRenderer::DirectionalLight*> GetAllDirectionalLight()
		{
			std::vector<LowRenderer::DirectionalLight*> temp;
			for (int i = 0; i < component.size(); i++)
			{
				if (auto newData = dynamic_cast<LowRenderer::DirectionalLight*>(component[i]))
				{
					temp.emplace_back(newData);
				}
			}
			return(temp);
		}
		std::vector<LowRenderer::PointLight*> GetAllPointLight()
		{
			std::vector<LowRenderer::PointLight*> temp;
			for (int i = 0; i < component.size(); i++)
			{
				if (auto newData = dynamic_cast<LowRenderer::PointLight*>(component[i]))
				{
					temp.emplace_back(newData);
				}
			}
			return(temp);
		}
		std::vector<LowRenderer::SpotLight*> GetAllSpotLight()
		{
			std::vector<LowRenderer::SpotLight*> temp;
			for (int i = 0; i < component.size(); i++)
			{
				if (auto newData = dynamic_cast<LowRenderer::SpotLight*>(component[i]))
				{
					temp.emplace_back(newData);
				}
			}
			return(temp);
		}

		void Draw(uint32_t shader);
	};
}