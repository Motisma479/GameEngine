#pragma once
#include "Resources/IResource.hpp"
#include "Core/Maths/Maths.hpp"
#include <vector>
#include <string>

namespace Resources
{
	struct Vertex
	{
		Maths::sVector::Vector3 position;
		Maths::sVector::Vector2 textureUV;
		Maths::sVector::Vector3 normal;

		bool operator==(const Vertex& v);
	};

	class Mesh : public IResources
	{
	public:
		void Create(const char* name);
		void Delete();
		void Draw();
		Mesh();

		unsigned int VBO, VAO, EBO;
		std::vector<Vertex> d_Vertex;
		std::vector<uint32_t> d_Index;
		std::string name;
	};
}
