#include "LoseScene.h"
#include "GameObject.h"
LoseScene::LoseScene()
	:GameScene{"LoseScene"}
{
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
