#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "Texture2D.h"
LVB::GameObject::GameObject()
	:m_pComponents{ std::vector<BaseComponent*>{} }
	,m_pTransform{nullptr}
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

void LVB::GameObject::Update(float elapsedSec)
{
	//std::cout << m_pComponents.size() << std::endl;
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(elapsedSec);
	}

}

void LVB::GameObject::Render() const
{
	const auto pos = m_pTransform->GetPosition();
	if(m_Texture != nullptr)
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void LVB::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void LVB::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}
