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
#include "PhysicsDebugRenderer.h"
#include "../GameBase/ContactListener.h"
LVB::BubbleBobbleScene::BubbleBobbleScene()
	:GameScene("Gamescene")
	,m_Level{}
	, m_PhysicsWorld{nullptr}
{
	Initialize();
}

LVB::BubbleBobbleScene::~BubbleBobbleScene()
{
	delete m_PhysicsWorld;
	delete m_DebugRenderer;
	delete m_Listener;
}

void LVB::BubbleBobbleScene::Initialize()
{
	m_Listener = new ContactListener{};
	m_DebugRenderer =  new PhysicsDebugRenderer{};
	const b2Vec2 gravity{ 0,50 };
	m_PhysicsWorld = new b2World{ gravity };
	//in constructor, usually
	m_PhysicsWorld->SetDebugDraw(m_DebugRenderer);

	//somewhere appropriate
	m_DebugRenderer->SetFlags(b2Draw::e_shapeBit);
	Renderer::GetInstance().SetScale(2.f);
	Renderer::GetInstance().SetOrigin(-36, -32);
	
	BinaryReader file("../data/BBSprites/leveldata.dat");
	std::vector<Level> levels(100);
	int level{ 2};
	for (std::size_t i{ 0 }; i < 100; ++i)
	{
		file >> levels[i];
	}
	auto positions = levels[level].BlockPositions();
	
	for (int i{ 0 }; i < positions.size(); ++i)
	{
		GameObject* go = new GameObject{};
		go->SetTexture("BBsprites/blocks.png");
		go->SetSprite({ 0 + (8 * level),0 }, 8, 8, 10, 10);
		go->GetTransform()->SetPosition(positions[i].x * go->GetSprite()->GetSpriteSheet()->GetSpriteWidth() , positions[i].y * go->GetSprite()->GetSpriteSheet()->GetSpriteHeight(), 0);
		b2BodyDef collider;
		collider.position.Set(positions[i].x * go->GetSprite()->GetSpriteSheet()->GetSpriteWidth(), positions[i].y * go->GetSprite()->GetSpriteSheet()->GetSpriteHeight());
		b2Body* body = m_PhysicsWorld->CreateBody(&collider);
		b2PolygonShape box;
		box.SetAsBox(4, 4);
		body->CreateFixture(&box, 0.0f);
		AddGameObject(go);
	}

	Character* player = new Character{ Character::Type::bob,8,2,16 ,m_PhysicsWorld,{32,170},this };
	this->AddGameObject(player);
	m_Listener->SetCharacter(player);

	m_PhysicsWorld->SetContactListener(m_Listener);
}

void LVB::BubbleBobbleScene::Update(float)
{

}

void LVB::BubbleBobbleScene::LateUpdate(float)
{
	m_PhysicsWorld->Step(1.f / 60.f, 8, 8);
}
void LVB::BubbleBobbleScene::Render() const
{
	m_PhysicsWorld->DebugDraw();
}
