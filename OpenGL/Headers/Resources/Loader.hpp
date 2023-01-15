#pragma once
#include "Core/Maths/Maths.hpp"
#include "Resources/manager/ResourcesManager.hpp"
#include "Resources/manager/MeshManager.hpp"
#include "Resources/manager/MaterialManager.hpp"


	class Loader
	{
	protected:
		static void SetVertex(const char* name, const char* nameOffMesh, Resources::ResourcesManager* resourceManager, Resources::MeshManager* meshManager, std::vector<Maths::sVector::Vector3> position, std::vector<Maths::sVector::Vector2> textureUV, std::vector<Maths::sVector::Vector3> normal, std::vector<int> vertexOrder, short orderType);
		static void LoadinGL(Resources::Mesh* tempMesh);
	public:
		static void LoadMatrerial(const char* name, Resources::ResourcesManager* resourceManager, Resources::MaterialManager* materialManager);
		static void loadModel(const char* name, Resources::ResourcesManager* resourceManager, Resources::MeshManager* meshManager, Resources::MaterialManager* materialManager);
	};
