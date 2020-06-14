#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include <future>
//bron http://www.cplusplus.com/reference/future/async/?kw=async
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
	m_pToRemove.push_back(obj);
}

const std::vector<LVB::GameObject*>& LVB::GameScene::GetGameObjects() const
{
	return m_pGameObjects;
}

void LVB::GameScene::RootRender() const
{
	for (GameObject* object : GetGameObjects())
	{
		object->RootRender();
	}
	Render();
}
void LVB::GameScene::RootUpdate(float elapsedSec)
{


	//Amount of gameobject per thread (except for the last thread)
	//If you multiply the size of a x86 pointer (4bytes) with 16 you get 64bytes which is the normal size of a cache line
	//this is a fix for false sharing (see photo in resources)
	static const int clusterSize{16};
	static const std::size_t threadCount{ 4 };
	Update(elapsedSec);
	for (int i{ 0 }; i < m_pToRemove.size(); ++i)
		pRemoveGameObject(m_pToRemove[i]);

	m_pToRemove.clear();
	//Making 4 threads
	std::vector<std::future<void>> futures;
	futures.reserve(threadCount);

	std::size_t begin{0};

	std::size_t sizeList{ m_pGameObjects.size() };
	std::size_t t = sizeList / clusterSize;
	//Launching 4 threads
	for (std::size_t i{ 0 }; i < threadCount - 1; ++i)
	{
		std::size_t end{};
		if ((t % threadCount) <= i)
		{
			end = t / threadCount;
		}
		else
		{
			end = t / threadCount + 1;
		}
		end *= clusterSize;
		end += begin;
		futures.push_back(std::async(UpdateGameObjects, this, elapsedSec, begin,end));
		begin = end;
	}
	futures.push_back(std::async(UpdateGameObjects, this, elapsedSec, begin, sizeList));


	//Wait for all thread to complete
	for (auto& fut : futures)
	{
		fut.get();
	}


}

void LVB::GameScene::UpdateGameObjects(GameScene* scene,float elapsedSec, std::size_t begin, std::size_t end)
{
	auto& objects = scene->GetGameObjects();
	for (std::size_t i{ begin }; i < end; ++i)
	{
		objects[i]->RootUpdate(elapsedSec);
	}
}

void LVB::GameScene::pRemoveGameObject(GameObject* obj)
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
