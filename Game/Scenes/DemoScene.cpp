#include "MiniginPCH.h"
#include "DemoScene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
LVB::DemoScene::DemoScene()
	:GameScene("DemoScene")
	,m_fpsCounter{nullptr}
{
	Initialize();
}

void LVB::DemoScene::Initialize()
{
	auto go = new GameObject{};
	go->SetTexture("background.jpg");
	this->AddGameObject(go);

	go = new GameObject{};
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	this->AddGameObject(go);


	go = new GameObject{};
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->SetPosition(80, 20);
	go->AddComponent(new TextComponent{ "Programming 4 Assignment", font });
	this->AddGameObject(go);
	
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	m_fpsCounter = new GameObject{};
	m_fpsCounter->SetPosition(0, 0);
	TextComponent* fps = new TextComponent{ "FPS: ", font };
	//fps->SetColor(SDL_Color{ 1,1,0,1 });
	m_fpsCounter->AddComponent(fps);
	this->AddGameObject(m_fpsCounter);

}

void LVB::DemoScene::Update(float elapsedSec)
{
	std::string text = "FPS: ";
	int fps = SceneManager::GetInstance().GetNumberOfFrames();
	text += std::to_string(fps);
	m_fpsCounter->GetComponent<TextComponent>()->SetText(text);


	
}

void LVB::DemoScene::LateUpdate(float)
{
}

void LVB::DemoScene::Render() const
{

}
