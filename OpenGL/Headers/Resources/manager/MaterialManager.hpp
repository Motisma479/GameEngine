#pragma once
#include "Resources/Material.hpp"
#include <vector>

namespace Resources
{

	class MaterialManager
	{
	private:
		std::vector<Material*> data;
	public:
		void AddData(Material* newData);
		int length();
		Material* GetData(int id);
		void Delete(const char* name);
		void GetPlace(const char* name);
	};
}