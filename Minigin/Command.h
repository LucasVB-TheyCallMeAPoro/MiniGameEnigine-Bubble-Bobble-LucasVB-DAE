#pragma once
namespace LVB
{
	class GameObject;
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(GameObject* actor) = 0;
	};
}

