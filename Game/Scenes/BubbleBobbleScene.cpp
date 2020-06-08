#include "BubbleBobbleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "../GameBase/Character.h"
#include "BinaryReader.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Spritesheet.h"
#include "Renderer.h"
LVB::BubbleBobbleScene::BubbleBobbleScene()
	:GameScene("Gamescene")
	,m_Level{}
{
	Initialize();
}

void LVB::BubbleBobbleScene::Initialize()
{
	Renderer::GetInstance().SetScale(2.f);
	Renderer::GetInstance().SetOrigin(-32, -40);
	Character* player = new Character{Character::Type::bob,8,1,16};
	player->AddComponent(new BoxCollider{ glm::vec2{2,2},3,3 });
	this->AddGameObject(player);
	BinaryReader file("../data/BBSprites/leveldata.dat");
	std::vector<Level> levels(100);
	for (std::size_t i{ 0 }; i < 100; ++i)
	{
		file >> levels[i];
	}
	auto positions = levels[0].BlockPositions();
	
	for (int i{ 0 }; i < positions.size(); ++i)
	{
		GameObject* go = new GameObject{};
		go->SetTexture("BBsprites/blocks.png");
		go->SetSprite({ 0,0 }, 8, 8, 10, 10);
		go->GetTransform()->SetPosition(positions[i].x * go->GetSprite()->GetSpriteSheet()->GetSpriteWidth() , positions[i].y * go->GetSprite()->GetSpriteSheet()->GetSpriteHeight(), 0);
	
		AddGameObject(go);
	}
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
