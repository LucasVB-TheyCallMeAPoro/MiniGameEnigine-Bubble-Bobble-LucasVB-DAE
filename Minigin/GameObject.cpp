#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Spritesheet.h"

LVB::GameObject::GameObject()
	:m_pComponents{ std::vector<BaseComponent*>{} }
	,m_pTransform{nullptr}
	,m_IsActive{true}
	,m_Sprite{nullptr}
	,m_SpriteSheet{nullptr}
	,m_Texture{nullptr}
{
	m_pTransform = new Transform();
	AddComponent(m_pTransform);
}

LVB::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
	if (m_Texture != nullptr)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
	if (m_Sprite != nullptr)
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}
	if (m_SpriteSheet != nullptr)
	{
		delete m_SpriteSheet;
		m_SpriteSheet = nullptr;
	}
}

void LVB::GameObject::AddComponent(BaseComponent * pComp)
{
	if (typeid(*pComp) == typeid(Transform) && HasComponent<Transform>())
	{
		std::cout << "GameObject::AddComponent > GameObject can contain only one TransformComponent!\n";
		return;
	}

	for (auto* component : m_pComponents)
	{
		if (component == pComp)
		{
			std::cout << "GameObject::AddComponent > GameObject already contains this component!\n";
			return;
		}
	}

	m_pComponents.push_back(pComp);
	pComp->SetGameObject(this);
}

void LVB::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it == m_pComponents.end())
	{
		std::cout << "GameObject::RemoveComponent > Component is not attached to this GameObject!\n";
		return;
	}

	if (typeid(*pComp) == typeid(Transform))
	{
		std::cout << "GameObject::RemoveComponent > TransformComponent can't be removed!\n";
		return;
	}

	m_pComponents.erase(it);
	pComp->SetGameObject(nullptr);
}

void LVB::GameObject::Update(float)
{

}

void LVB::GameObject::Render() const
{
	
}

void LVB::GameObject::RootUpdate(float elapsedSec)
{
	if (!m_IsActive)
		return;

	Update(elapsedSec);

	//Component Update
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(elapsedSec);
	}

}

void LVB::GameObject::RootRender() const
{
	const auto pos = m_pTransform->GetPosition();
	if (m_Texture != nullptr && m_Sprite == nullptr)
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	if (m_Sprite != nullptr)
	{
		Renderer::GetInstance().RenderSprite(*m_Sprite, pos.x, pos.y);
	}

	Render();
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void LVB::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void LVB::GameObject::SetSprite(const glm::ivec2& origin, int spriteWidth, int spriteHeight, int columnCount, int rowCount)
{
	if (m_Texture == nullptr)
	{
		std::cout << "You forgot to add your texture!\n";
		return;
	}
	m_SpriteSheet = new SpriteSheet(m_Texture, origin, spriteWidth, spriteHeight, columnCount, rowCount);
	m_Sprite = new Sprite(m_SpriteSheet);
}

void LVB::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}
