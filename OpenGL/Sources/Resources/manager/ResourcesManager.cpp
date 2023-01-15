#include "Resources/manager/ResourcesManager.hpp"
#include "Core/Debug/Debug.hpp"

void Resources::ResourcesManager::Delete(const char* name)
{
	if (data.count(name) > 0) {
		Resources::IResources* temp = data.find(name)->second;
		temp->Delete();
		data.erase(name);
	}
	else
		DEBUG_LOG("Warning: can't delete a non-existing element!");
}

void Resources::ResourcesManager::GetPlace(const char* name)
{
	if (data.count(name) > 0)
		std::cout << "data has " << name << " ,Value: " << data.count(name) << std::endl;
	else
		std::cout << "data has no " << name << std::endl;

}