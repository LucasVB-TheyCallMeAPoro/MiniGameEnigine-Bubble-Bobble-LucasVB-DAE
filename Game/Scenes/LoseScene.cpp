#include "LoseScene.h"
#include "GameObject.h"
#include "Renderer.h"
LoseScene::LoseScene()
	:GameScene{"LoseScene"}
{
	LVB::Renderer::GetInstance().SetScale(1.f);
	LVB::Renderer::GetInstance().SetOrigin(0, 0);
	auto go = new LVB::GameObject{};
	go->SetTexture("BBSprites/LoseScreen.png");
	this->AddGameObject(go);
}

void LoseScene::Initialize()
{
}

void LoseScene::Update(float elapsedSec)
{
}

void LoseScene::LateUpdate(float elapsedSec)
{
}

void LoseScene::Render() const
{
}
