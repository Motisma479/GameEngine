#pragma once
#include "LowRenderer/Component.hpp"

#include "Resources/Mesh.hpp"
#include "Resources/Material.hpp"

#include "Resources/manager/MeshManager.hpp"
#include "Resources/manager/MaterialManager.hpp"

#include "Utils.hpp"

#include <vector>

namespace LowRenderer
{
	class Model : public Component
	{
	private:
		std::vector<Resources::Mesh*> mesh;
		std::vector<Resources::Material*> material; //Texture set in

	public:
		Model();
		~Model();
		void Draw(uint32_t& shader);

		void DrawInIMGUI(Resources::MeshManager& meshManager, Resources::MaterialManager& materialManager);
	};
}