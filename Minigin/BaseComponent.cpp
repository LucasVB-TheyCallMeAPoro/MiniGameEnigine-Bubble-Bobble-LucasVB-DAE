#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Transform.h"
#include "GameObject.h"
using namespace LVB;
BaseComponent::BaseComponent() 
	: m_pGameObject(nullptr)
{
}

LVB::Transform* BaseComponent::GetTransform() const
{
	if (m_pGameObject == nullptr)
	{
		std::cout << "BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL.\n";
		return nullptr;
	}

	return m_pGameObject->GetTransform();
}

void LVB::BaseComponent::SetGameObject(GameObject* go)
{
	m_pGameObject = go;
}

