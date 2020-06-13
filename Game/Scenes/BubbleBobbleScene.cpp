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

#include "SceneManager.h"
LVB::BubbleBobbleScene::BubbleBobbleScene()
	:GameScene("Gamescene")
	, m_PhysicsWorld{nullptr}
	,m_Player1UI{}
	,m_Player2UI{}
	, m_DebugRenderer{}
	, m_Listener{}
	,m_LevelNumber{1}
	, m_Levels{}
	,m_Player1{}
{
	Initialize();
}

LVB::BubbleBobbleScene::~BubbleBobbleScene()
{
	delete m_PhysicsWorld;
	delete m_DebugRenderer;
	delete m_Listener;
	delete m_Player1UI;
	delete m_Player2UI;
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
	Renderer::GetInstance().SetOrigin(-36,-40);
	
	
	InitLevel();
	InitPlayer();

	m_PhysicsWorld->SetContactListener(m_Listener);
}

void LVB::BubbleBobbleScene::Update(float elapsedSec)
{
	m_Player1UI->Update();

}

void LVB::BubbleBobbleScene::LateUpdate(float)
{
	m_PhysicsWorld->Step(1.f / 60.f, 8, 8);
}
void LVB::BubbleBobbleScene::Render() const
{
	m_PhysicsWorld->DebugDraw();
}

void LVB::BubbleBobbleScene::InitLevel()
{
	BinaryReader file("../data/BBSprites/leveldata.dat");
	m_Levels.resize(100);
	m_LevelBodies.reserve(100);
	m_LevelObjects.reserve(100);
	for (std::size_t i{ 0 }; i < 100; ++i)
	{
		file >> m_Levels[i];
	}
	auto positions = m_Levels[m_LevelNumber].BlockPositions();

	for (int i{ 0 }; i < positions.size(); ++i)
	{
		m_LevelObjects.push_back(new GameObject{});
		m_LevelObjects.back()->SetTexture("BBsprites/blocks.png");
		m_LevelObjects.back()->SetSprite({ 0 + (8 * m_LevelNumber ),0 }, 8, 8, 10, 10);
		m_LevelObjects.back()->GetTransform()->SetPosition(positions[i].x * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteWidth(), positions[i].y * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteHeight(), 0);
		b2BodyDef collider;
		collider.position.Set(positions[i].x * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteWidth(), positions[i].y * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteHeight());
		m_LevelBodies.push_back(m_PhysicsWorld->CreateBody(&collider));
		b2PolygonShape box;
		box.SetAsBox(4, 4);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.filter.categoryBits = BOUNDARY;
		fixtureDef.filter.groupIndex = CHARACTER | ENEMY;
		
		if (positions[i].x > 1 && positions[i].y > 0 && positions[i].x < 30)
			fixtureDef.filter.categoryBits = PLATFORM;

		m_LevelBodies.back()->CreateFixture(&fixtureDef);
		
		
			

		AddGameObject(m_LevelObjects.back());
	}
}

void LVB::BubbleBobbleScene::InitPlayer()
{
	m_Player1 = new Character{ Character::Type::bob,8,2,16 ,m_PhysicsWorld,{32,170},this,BubbleBobbleScene::CHARACTER, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY };
	this->AddGameObject(m_Player1);
	m_Listener->SetCharacter(m_Player1);
	m_Player1UI = new UI{ m_Player1,UI::ScreenPos::player1,this };
	m_Player1->NotifyUI();

}

void LVB::BubbleBobbleScene::LoadNewLevel()
{
	for (int i{ 0 }; i < m_LevelBodies.size(); ++i)
	{
		this->RemoveGameObject(m_LevelObjects[i]);
		m_PhysicsWorld->DestroyBody(m_LevelBodies[i]);
	}
	m_LevelBodies.clear();
	m_LevelObjects.clear();
	m_LevelNumber++;
	auto positions = m_Levels[m_LevelNumber].BlockPositions();
	m_LevelBodies.reserve(100);
	m_LevelObjects.reserve(100);
	
	for (int i{ 0 }; i < positions.size(); ++i)
	{
		m_LevelObjects.push_back(new GameObject{});
		m_LevelObjects.back()->SetTexture("BBsprites/blocks.png");
		m_LevelObjects.back()->SetSprite({ 0 + (8 * m_LevelNumber),0 }, 8, 8, 10, 10);
		m_LevelObjects.back()->GetTransform()->SetPosition(positions[i].x * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteWidth(), positions[i].y * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteHeight(), 0);
		b2BodyDef collider;
		collider.position.Set(positions[i].x * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteWidth(), positions[i].y * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteHeight());
		m_LevelBodies.push_back(m_PhysicsWorld->CreateBody(&collider));
		b2PolygonShape box;
		box.SetAsBox(4, 4);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.filter.categoryBits = BOUNDARY;
		fixtureDef.filter.groupIndex = CHARACTER | ENEMY;

		if (positions[i].x > 1 && positions[i].y > 0 && positions[i].x < 30)
			fixtureDef.filter.categoryBits = PLATFORM;

		m_LevelBodies.back()->CreateFixture(&fixtureDef);
		AddGameObject(m_LevelObjects.back());
	}

	m_Player1->SetToSpawnPos();
}
