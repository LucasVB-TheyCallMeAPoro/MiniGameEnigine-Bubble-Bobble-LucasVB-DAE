#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"
void dae::SceneManager::Update(float elapsed)
{
	for (GameScene* scene : m_GameScenes)
	{
		scene->Update(elapsed);
	}
}

void dae::SceneManager::Render()
{
	for (GameScene* scene : m_GameScenes)
	{
		scene->Render();
	}
}

dae::SceneManager::~SceneManager()
{
	/*for (int i{ 0 }; i < m_GameScenes.size(); ++i)
	{
		delete m_GameScenes[i];
	}*/
}

void dae::SceneManager::CreateScene(GameScene* gs)
{
	const auto it = std::find(m_GameScenes.begin(), m_GameScenes.end(), gs);

	if (it == m_GameScenes.end())
	{
		m_GameScenes.push_back(gs);
	}
}
