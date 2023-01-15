#pragma once
#include "Resources/IResource.hpp"

#include <unordered_map>
namespace Resources
{
	class ResourcesManager
	{
	private:
		std::unordered_map<const char*, Resources::IResources*> data;
	public:
		template <typename T>
		T* Create(const char* name)
		{
			T* temp = new T;

			temp->Create(name);
			data.emplace(name, (IResources*)temp);
			return temp;
		}

		template <typename T>
		void AddData(const char* name, T* newData)
		{
			data.emplace(name, (IResources*)newData);
		}

		template <typename T>
		T* Get(const char* name)
		{
			Resources::IResources* temp = data.find(name)->second;
			if (temp == NULL)
				return nullptr;
			return (T*)temp;
		}
		void Delete(const char* name);
		void GetPlace(const char* name);
	};
}