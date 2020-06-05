#pragma once
#include <string>
#include <vector>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace LVB
{
	class BaseComponent;
	class Transform;
	class Texture2D;
	class SpriteSheet;
	class Sprite;
	class GameObject
	{
	public:
	
		void SetTexture(const std::string& filename);
		void SetSprite(const glm::ivec2& origin, int spriteWidth, int spriteHeight, int columnCount, int rowCount);
		void SetPosition(float x, float y);
		void SetActive(bool input) { m_IsActive = input; }

		Texture2D* GetTexture() const { return m_Texture; }
		Sprite* GetSprite() const { return m_Sprite; }
		Transform* GetTransform() const { return m_pTransform; };
		GameObject();
		~GameObject();

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);
		template <class T>
		T* GetComponent();
		template <class T>
		bool HasComponent();
	protected:
		virtual void Update(float elapsed);
		virtual void Render() const;
	private:
		friend class GameScene;
		void RootUpdate(float);
		void RootRender() const;
		Transform* m_pTransform;

		Texture2D* m_Texture;
		SpriteSheet* m_SpriteSheet;
		Sprite* m_Sprite;

		std::vector<BaseComponent*> m_pComponents;
		bool m_IsActive;
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


