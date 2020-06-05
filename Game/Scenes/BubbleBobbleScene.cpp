#include "BubbleBobbleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "../Character.h"
LVB::BubbleBobbleScene::BubbleBobbleScene()
	:GameScene("Gamescene")
{
	Initialize();
}

void LVB::BubbleBobbleScene::Initialize()
{
	Character* player = new Character{Character::Type::bob,8,1,16};
	player->AddComponent(new BoxCollider{ glm::vec2{2,2},3,3 });
	this->AddGameObject(player);
}

void LVB::BubbleBobbleScene::Update(float)
{
}

void LVB::BubbleBobbleScene::LateUpdate(float)
{

}
void LVB::BubbleBobbleScene::Render() const
{
}
