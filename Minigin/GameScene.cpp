#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
dae::GameScene::GameScene(std::string sceneName)
	:m_SceneName{sceneName}
	,m_pGameObjects(std::vector<GameObject*>())
{
}

dae::GameScene::~GameScene()
{
	for (auto pGO : m_pGameObjects)
	{
		delete pGO;
		pGO = nullptr;
	}
}

void dae::GameScene::AddGameObject(GameObject* obj)
{
	if (obj == nullptr)
	{
		std::cout << "Gameobject is a nullptr! \n";
		return;
	}

	m_pGameObjects.push_back(obj);
}

void dae::GameScene::RemoveGameObject(GameObject* obj)
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

const std::vector<dae::GameObject*>& dae::GameScene::GetGameObjects() const
{
	return m_pGameObjects;
}
