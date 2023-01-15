#pragma once
namespace LowRenderer
{
	class Component
	{
	public:
		//virtual void UnConstructor();
		virtual void DrawInIMGUI();
		virtual void Draw();
	};
}