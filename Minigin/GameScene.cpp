#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
LVB::GameScene::GameScene(std::string sceneName)
	:m_SceneName{sceneName}
	,m_pGameObjects(std::vector<GameObject*>())
{
}

LVB::GameScene::~GameScene()
{
	for (auto pGO : m_pGameObjects)
	{
		delete pGO;
		pGO = nullptr;
	}
}

void LVB::GameScene::AddGameObject(GameObject* obj)
{
	if (obj == nullptr)
	{
		std::cout << "Gameobject is a nullptr! \n";
		return;
	}

	m_pGameObjects.push_back(obj);
}

void LVB::GameScene::RemoveGameObject(GameObject* obj)
{
	const auto it = find(m_pGameObjects.begin(), m_pGameObjects.end(), obj);
	if (it == m_pGameObjects.end())
	{
		std::cout << "Gameobject is not found!\n";
		return;
	}

	m_pGameObjects.erase(it);
	delete obj;
	obj = nullptr;
}

const std::vector<LVB::GameObject*>& LVB::GameScene::GetGameObjects() const
{
	return m_pGameObjects;
}
