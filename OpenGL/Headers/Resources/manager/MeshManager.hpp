#pragma once
#include "Resources/Mesh.hpp"
#include <vector>

namespace Resources
{
	
	class MeshManager
	{
	private:
		std::vector<Mesh*> data;
	public:
		void AddData(Mesh* newData);
		Mesh* GetData(int id);
		int length();
		void Delete(const char* name);
		void GetPlace(const char* name);
	};
}