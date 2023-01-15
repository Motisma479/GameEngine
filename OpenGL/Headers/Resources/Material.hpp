#pragma once
#include "Resources/IResource.hpp"

#include "Resources/Texture.hpp"

#include "Core/Maths/Maths.hpp"
#include <vector>
#include <string>
namespace Resources
{

	class Material : public IResources
	{
	public:
		Maths::sVector::Vector3 ambient;
		Maths::sVector::Vector3 diffuse;
		Maths::sVector::Vector3 specular;
		Maths::sVector::Vector3 emisive;
		float shininess;
		
		Resources::Texture* TextureRef;

		std::string name;

		void Create(const char* name);
		void Link(uint32_t shader);
		void Delete();
		Material();
	};
}
