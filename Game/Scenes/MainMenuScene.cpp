#include "MainMenuScene.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Transform.h"
#include "InputManager.h"
MainMenu::MainMenu()
	:GameScene{"Mainmenu"}
	,m_LoadCoop{}
	,m_LoadSolo{}
	,m_LoadVS{}
{
	Initialize();
}

MainMenu::~MainMenu()
{
	
}

void MainMenu::Initialize()
{
	m_LoadCoop = new Button{ 0,0,std::bind(LoadGame,LVB::BubbleBobbleScene::coop) };
	m_LoadCoop->SetTexture("CoopButton.png");
	m_LoadCoop->SetWidthAndHeight(m_LoadCoop->GetTexture()->GetWidth(), m_LoadCoop->GetTexture()->GetHeight());
	m_LoadCoop->GetTransform()->SetPosition(640 / 2 - m_LoadCoop->GetTexture()->GetWidth()/2, 480 / 2 + 128, 0);
	AddGameObject(m_LoadCoop);

	m_LoadSolo = new Button{ 0,0,std::bind(LoadGame,LVB::BubbleBobbleScene::solo) };
	m_LoadSolo->SetTexture("SoloButton.png");
	m_LoadSolo->SetWidthAndHeight(m_LoadCoop->GetTexture()->GetWidth(), m_LoadCoop->GetTexture()->GetHeight());
	m_LoadSolo->GetTransform()->SetPosition(640 / 2 - m_LoadCoop->GetTexture()->GetWidth()/2, 480 / 2, 0);
	AddGameObject(m_LoadSolo);

	m_LoadVS = new Button{ 0,0,std::bind(LoadGame,LVB::BubbleBobbleScene::vs) };
	m_LoadVS->SetTexture("VSButton.png");
	m_LoadVS->SetWidthAndHeight(m_LoadCoop->GetTexture()->GetWidth(), m_LoadCoop->GetTexture()->GetHeight());
	m_LoadVS->GetTransform()->SetPosition(640 / 2 - m_LoadCoop->GetTexture()->GetWidth()/2, 480 / 2 - 128, 0);
	AddGameObject(m_LoadVS);
}

void MainMenu::Update(float elapsedSec)
{
	int x;
	int y;
	if (LVB::InputManager::GetInstance().GetClick(&x, &y))
	{
		m_LoadCoop->HandleClick(x,y);
		m_LoadSolo->HandleClick(x, y);
		m_LoadVS->HandleClick(x, y);
	}
}

void MainMenu::LateUpdate(float elapsedSec)
{
}

void MainMenu::Render() const
{
}

void MainMenu::LoadGame(LVB::BubbleBobbleScene::GameType type)
{
	LVB::SceneManager::GetInstance().CreateScene(new LVB::BubbleBobbleScene{ type });
	LVB::SceneManager::GetInstance().SetActiveGameScene("BubbleBobbleScene");
}

