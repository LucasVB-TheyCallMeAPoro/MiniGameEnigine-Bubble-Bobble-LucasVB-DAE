#pragma once

namespace LVB
{
	class GameObject;
	class Transform;
	class BaseComponent
	{
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = default;

		GameObject* GetGameObject() const { return m_pGameObject; }
		Transform* GetTransform() const;
		void SetGameObject(GameObject* go);

		virtual void Render() const = 0;
		virtual void Update(float elapsedSec) = 0;
		virtual void Initialize() = 0;
		
	protected:
		GameObject* m_pGameObject;
	};
}