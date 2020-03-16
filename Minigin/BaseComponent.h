#pragma once

namespace dae
{
	class GameObject;
	class Transform;
	class BaseComponent
	{
		void RootInitialize();
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
	protected:

		virtual void Initialize() = 0;
		virtual void Update(float elapsedSec) = 0;
		virtual void Draw() = 0;
		virtual void PostDraw() {}

		GameObject* m_pGameObject;
	};
}