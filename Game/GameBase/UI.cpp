#include "UI.h"
#include "Character.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameScene.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Font.h"

UI::UI(Character* character, ScreenPos pos, LVB::GameScene* scene)
	:m_HealthListener{}
	, m_ScoreListener{}
	,m_Character{character}
	,m_Pos{pos}
	, m_ScoreObject{}
	, m_HealthObject{}
{
	m_Character->m_OnChangeScore.AddListener(&m_ScoreListener);
	m_Character->m_OnChangeHealth.AddListener(&m_HealthListener);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	switch (pos)
	{
	case UI::ScreenPos::player1:
	{
		m_ScoreObject = new LVB::GameObject{};
		m_ScoreObject->SetPosition(0 , -32);
		m_ScoreObject->AddComponent(new TextComponent{ std::to_string(m_ScoreListener.m_Score), font });
		m_ScoreObject->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255,255,0,255 });
		scene->AddGameObject(m_ScoreObject);

		m_HealthObject = new LVB::GameObject{};
		m_HealthObject->SetPosition(0 , -18);
		m_HealthObject->AddComponent(new TextComponent{ std::to_string(m_HealthListener.m_Health),font });
		m_HealthObject->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255,0,0,255 });
		scene->AddGameObject(m_HealthObject);
		
		font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);	
		m_LevelNumberObject = new LVB::GameObject{};
		m_LevelNumberObject->SetPosition(110, -40);
		m_LevelNumberObject->AddComponent(new TextComponent{ std::to_string(1),font });
		m_LevelNumberObject->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0,0,0,255 });
		scene->AddGameObject(m_LevelNumberObject);
	}
		break;
	case UI::ScreenPos::player2:
	{
		m_ScoreObject = new LVB::GameObject{};
		m_ScoreObject->SetPosition(230, -32);
		m_ScoreObject->AddComponent(new TextComponent{ std::to_string(m_ScoreListener.m_Score), font });
		m_ScoreObject->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255,255,0,255 });
		scene->AddGameObject(m_ScoreObject);

		m_HealthObject = new LVB::GameObject{};
		m_HealthObject->SetPosition(230, -18);
		m_HealthObject->AddComponent(new TextComponent{ std::to_string(m_HealthListener.m_Health),font });
		m_HealthObject->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255,0,0,255 });
		scene->AddGameObject(m_HealthObject);
	}
		break;
	}
}

void UI::Render() const
{

}

void UI::Update()
{
	m_HealthObject->GetComponent<TextComponent>()->SetText(std::to_string(m_HealthListener.m_Health));
	m_ScoreObject->GetComponent<TextComponent>()->SetText(std::to_string(m_ScoreListener.m_Score));
}

void UI::SetLevelNumber(int i)
{
	m_LevelNumberObject->GetComponent<TextComponent>()->SetText(std::to_string(i));
}
