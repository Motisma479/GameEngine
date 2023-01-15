#pragma once
namespace Resources
{
	__interface IResources
	{
	public:
		void Create(const char* name);
		void Delete();
	};
}