#pragma once
#include "Core/DataStructure/Node.hpp"

//#include "Resources/Texture.hpp"
namespace DataStructure
{
	class Scene
	{
	private:
		std::vector<DataStructure::Node*> data;
		int selected;
	public:
		Scene();
		~Scene();
		void DrawGraph(bool& windowExist, const bool& active);
		void Draw(Maths::sMatrix::Mat4 VP, uint32_t shader);
		void DrawNode(bool& windowExist, const bool& active, Resources::MeshManager& meshManager, Resources::MaterialManager& materialManager);
		//Node(const Maths::sVector::Vector3 p_Position, const Maths::sVector::Vector3 p_Rotation, const Maths::sVector::Vector3 p_Scale, Resources::Model* p_Models, Resources::Texture* p_Texture);
		//void Update(Maths::sMatrix::Mat4 VP, uint32_t shader);
	};
}