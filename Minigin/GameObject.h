#pragma once

namespace dae
{
	class BaseComponent;
	class Transform;
	class Texture2D;
	class GameObject
	{
	public:
		void Update(float elapsed);
		void Render() const;
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		Transform* GetTransform() const { return m_pTransform; };
		GameObject();
		virtual ~GameObject();

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);
		template <class T>
		T* GetComponent();
		template <class T>
		bool HasComponent();
	private:
		Transform* m_pTransform;
		Texture2D* m_Texture;
		std::vector<BaseComponent*> m_pComponents;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};

	//Templated functions
	template<class T>
	inline T* GameObject::GetComponent()
	{
		const type_info& ti = typeid(T);
		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}
		return nullptr;
	}
	template<class T>
	inline bool GameObject::HasComponent()
	{
		return GetComponent<T>() != nullptr;
	}
}


