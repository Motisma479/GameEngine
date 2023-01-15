#include "Resources/manager/MaterialManager.hpp"

void Resources::MaterialManager::AddData(Material* newData)
{
	data.push_back(newData);
}
int Resources::MaterialManager::length()
{
	return data.size();
}
Resources::Material* Resources::MaterialManager::GetData(int id)
{
	return data[id];
}