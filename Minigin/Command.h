#pragma once
namespace LVB
{
	class GameObject;
	class Command
	{
	public:
		Command(GameObject* actor)
			:m_GameObject{actor}
		{}
		virtual ~Command() = default;
		virtual void Execute() = 0;

		GameObject* GetGameObject()const { return m_GameObject; }
	private:
		GameObject* m_GameObject;
	};
}

