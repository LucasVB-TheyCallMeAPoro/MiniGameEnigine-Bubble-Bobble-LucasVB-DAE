#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "BaseComponent.h"
dae::GameObject::GameObject()
	:m_pComponents{ std::vector<BaseComponent*>{} }
	,m_pTransform{nullptr}
{
	m_pTransform = new Transform();
	AddComponent(m_pTransform);
}

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
}

void dae::GameObject::AddComponent(BaseComponent * pComp)
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

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
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

void dae::GameObject::Update(float elapsedSec)
{
	//std::cout << m_pComponents.size() << std::endl;
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(elapsedSec);
	}

}

void dae::GameObject::Render() const
{
	const auto pos = m_pTransform->GetPosition();
	if(m_Texture != nullptr)
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}
