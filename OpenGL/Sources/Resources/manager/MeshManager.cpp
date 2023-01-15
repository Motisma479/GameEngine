#include "Resources/manager/MeshManager.hpp"

void Resources::MeshManager::AddData(Mesh* newData)
{
	data.push_back(newData);
}
Resources::Mesh* Resources::MeshManager::GetData(int id)
{
	return data[id];
}
int Resources::MeshManager::length()
{
	return data.size();
}