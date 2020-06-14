#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"
void LVB::SceneManager::Update(float elapsed)
{
	if (m_NewActiveScene != nullptr)
	{
		//Set New Scene
		m_ActiveScene = m_NewActiveScene;
		m_NewActiveScene = nullptr;
	}

	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->RootUpdate(elapsed);
	}
}

void LVB::SceneManager::LateUpdate(float elapsed)
{
	m_ActiveScene->LateUpdate(elapsed);
	
}

void LVB::SceneManager::SetActiveGameScene(std::string name)
{
	const auto it = std::find_if(m_GameScenes.begin(), m_GameScenes.end(), [name](GameScene* scene)
		{
			
			return scene->m_SceneName == name;
		});

	if (it != m_GameScenes.end())
	{
		m_NewActiveScene = *it;
	}
}

int LVB::SceneManager::GetNumberOfFrames() const
{
	return m_NrOfFrames;
}

void LVB::SceneManager::Render()
{
	m_ActiveScene->RootRender();
}

LVB::SceneManager::SceneManager()
	:m_ActiveScene{nullptr}
	, m_NewActiveScene{ nullptr }	
{
}

LVB::SceneManager::~SceneManager()
{
	for (std::size_t i{ 0 }; i < m_GameScenes.size(); ++i)
	{
		delete m_GameScenes[i];
	}
}

void LVB::SceneManager::CreateScene(GameScene* gs)
{
	const auto it = std::find(m_GameScenes.begin(), m_GameScenes.end(), gs);

	if (it == m_GameScenes.end())
	{
		m_GameScenes.push_back(gs);
		if (m_ActiveScene == nullptr)
			m_ActiveScene = gs;
	}
	else
	{
		std::cout << "GameScene already exists!\n";
	}
}

void LVB::SceneManager::SetNbOfFrames(int frames)
{
	m_NrOfFrames = frames;
}
