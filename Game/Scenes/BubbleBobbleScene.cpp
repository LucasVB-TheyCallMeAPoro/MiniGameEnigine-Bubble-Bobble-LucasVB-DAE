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
#include <random>
#include "TextComponent.h"
#include "InputManager.h"
#include "../Commands/GameCommands.h"
const int LVB::BubbleBobbleScene::keyPlatform{};
const int LVB::BubbleBobbleScene::keyWall{};
LVB::BubbleBobbleScene::BubbleBobbleScene(GameType type)
	:GameScene("BubbleBobbleScene")
	, m_PhysicsWorld{nullptr}
	,m_Player1UI{}
	,m_Player2UI{nullptr}
	, m_DebugRenderer{}
	, m_Listener{}
	,m_LevelNumber{0}
	, m_Levels{}
	,m_Player1{}
	, m_LevelText{}
	, m_NumberOfEnemies{}
	,m_Type{type}
{
	Initialize();
}

LVB::BubbleBobbleScene::~BubbleBobbleScene()
{
	delete m_PhysicsWorld;
	delete m_DebugRenderer;
	delete m_Listener;
	delete m_Player1UI;
	if(m_Player2UI != nullptr)
		delete m_Player2UI;
}

ContactListener* LVB::BubbleBobbleScene::GetListener() const
{
	return m_Listener;
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
	if(m_Type != GameType::vs)
		SpawnEnemies();

	InitControls();
	m_PhysicsWorld->SetContactListener(m_Listener);
}

void LVB::BubbleBobbleScene::Update(float elapsedSec)
{



	switch (m_Type)
	{
	case LVB::BubbleBobbleScene::solo:
		CheckLevel(elapsedSec);
		m_Player1UI->Update();
		break;
	case LVB::BubbleBobbleScene::coop:
		CheckLevel(elapsedSec);
		m_Player1UI->Update();
		m_Player2UI->Update();
		break;
	case LVB::BubbleBobbleScene::vs:
		break;
	}

	
		
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

	LoadLevel(positions);

}

void LVB::BubbleBobbleScene::InitPlayer()
{
	switch (m_Type)
	{
	case LVB::BubbleBobbleScene::solo:
	{
		m_Player1 = new Character{ Character::Player::Player1, Character::Type::Bub,8,2,16 ,m_PhysicsWorld,{32,170},this,BubbleBobbleScene::CHARACTER, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY | BubbleBobbleScene::BUBBLE | BubbleBobbleScene::PICKUP | BubbleBobbleScene::BOULDER };
		this->AddGameObject(m_Player1);
		m_Listener->AddCharacter(m_Player1);
		m_Player1UI = new UI{ m_Player1,UI::ScreenPos::player1,this };
		m_Player1->NotifyUI();
	}
		break;
	case LVB::BubbleBobbleScene::coop:
	{
		m_Player1 = new Character{ Character::Player::Player1, Character::Type::Bub,8,2,16 ,m_PhysicsWorld,{32,170},this,BubbleBobbleScene::CHARACTER, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY | BubbleBobbleScene::BUBBLE | BubbleBobbleScene::PICKUP | BubbleBobbleScene::BOULDER };
		this->AddGameObject(m_Player1);
		m_Listener->AddCharacter(m_Player1);
		m_Player1UI = new UI{ m_Player1,UI::ScreenPos::player1,this };

		m_Player2 = new Character{ Character::Player::Player2, Character::Type::bob,8,2,16 ,m_PhysicsWorld,{180,170},this,BubbleBobbleScene::CHARACTER, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY | BubbleBobbleScene::BUBBLE | BubbleBobbleScene::PICKUP | BubbleBobbleScene::BOULDER };
		this->AddGameObject(m_Player2);
		m_Listener->AddCharacter(m_Player2);
		m_Player2UI = new UI{ m_Player2,UI::ScreenPos::player2,this };
		m_Player1->NotifyUI();
		m_Player2->NotifyUI();
	}
		break;
	case LVB::BubbleBobbleScene::vs:
	{
		m_Player1 = new Character{ Character::Player::Player1, Character::Type::Bub,8,2,16 ,m_PhysicsWorld,{32,170},this,BubbleBobbleScene::CHARACTER, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY | BubbleBobbleScene::BUBBLE | BubbleBobbleScene::PICKUP | BubbleBobbleScene::BOULDER };
		this->AddGameObject(m_Player1);
		m_Listener->AddCharacter(m_Player1);
		m_Player1UI = new UI{ m_Player1,UI::ScreenPos::player1,this };

		m_Player2 = new Character{ Character::Player::Player1, Character::Type::Maita,8,2,16 ,m_PhysicsWorld,{32,170},this,BubbleBobbleScene::CHARACTER, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY | BubbleBobbleScene::BUBBLE | BubbleBobbleScene::PICKUP };
		this->AddGameObject(m_Player2);
		m_Listener->AddCharacter(m_Player2);
		m_Player2UI = new UI{ m_Player2,UI::ScreenPos::player2,this };
		m_Player1->NotifyUI();
		m_Player2->NotifyUI();
	}
		break;		
	}



}

void LVB::BubbleBobbleScene::LoadNewLevel()
{

	for (std::size_t i{ 0 }; i < m_LevelBodies.size(); ++i)
	{
		this->RemoveGameObject(m_LevelObjects[i]);
		m_PhysicsWorld->DestroyBody(m_LevelBodies[i]);
	}
	m_LevelBodies.clear();
	m_LevelObjects.clear();
	m_LevelNumber++;
	m_Player1UI->SetLevelNumber(static_cast<int>(m_LevelNumber));
	auto positions = m_Levels[m_LevelNumber].BlockPositions();
	m_LevelBodies.reserve(100);
	m_LevelObjects.reserve(100);
	
	LoadLevel(positions);
	if (m_Type == GameType::solo)
	{
		m_Player1->SetToSpawnPos();
	}
	else
	{
		m_Player1->SetToSpawnPos();
		m_Player2->SetToSpawnPos();
	}

	SpawnEnemies();
}

void LVB::BubbleBobbleScene::LoadLevel(const std::vector<glm::ivec2>& positions)
{

	for (std::size_t i{ 0 }; i < positions.size(); ++i)
	{
		m_LevelObjects.push_back(new GameObject{});
		m_LevelObjects.back()->SetTexture("BBsprites/blocks.png");
		m_LevelObjects.back()->SetSprite({ 0 + (8 * m_LevelNumber),0 }, 8, 8, 10, 10);
		m_LevelObjects.back()->GetTransform()->SetPosition(static_cast<float>(positions[i].x * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteWidth()), static_cast<float>(positions[i].y * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteHeight()), 0.f);
		b2BodyDef collider;
		collider.position.Set(static_cast<float>(positions[i].x * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteWidth()), static_cast<float>(positions[i].y * m_LevelObjects.back()->GetSprite()->GetSpriteSheet()->GetSpriteHeight()));
		m_LevelBodies.push_back(m_PhysicsWorld->CreateBody(&collider));
		b2PolygonShape box;
		box.SetAsBox(4, 4);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.filter.categoryBits = BOUNDARY;
		fixtureDef.filter.groupIndex = CHARACTER | ENEMY;
		fixtureDef.userData = (void*)&keyWall;
		if (positions[i].x > 1 && positions[i].y > 0 && positions[i].x < 30 )
		{
			fixtureDef.filter.categoryBits = PLATFORM;
			fixtureDef.userData = (void*)&keyPlatform;
		}
		m_LevelBodies.back()->CreateFixture(&fixtureDef);


		AddGameObject(m_LevelObjects.back());
	}
}

void LVB::BubbleBobbleScene::SpawnEnemies()
{
	m_Listener->ClearEnemies();
	m_NumberOfEnemies = static_cast<int>(m_LevelNumber) + 3;
	
	int randomNumOfMaita = 0;
	int spawnOffset = 40;
	if (m_LevelNumber > 0)
	{
		

		std::ranlux48 generator;
		std::uniform_int_distribution<int> distribution(1, m_NumberOfEnemies);
		randomNumOfMaita = distribution(generator);
	}
	glm::vec2 spawnPos{	70,20 };
	for (int i{ 0 }; i <  randomNumOfMaita; ++i)
	{
		auto state = Enemy::State::MoveLeft;
		if (i > randomNumOfMaita / 2)
			state = Enemy::State::MoveRight;

		Enemy* enemy = new Enemy{ i,state,Enemy::Type::Maita,spawnPos,8,2,16,this,m_PhysicsWorld,BubbleBobbleScene::ENEMY, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::CHARACTER | BubbleBobbleScene::BUBBLE };
		this->AddGameObject(enemy);
		m_Listener->AddEnemy(enemy);
		spawnPos.x += spawnOffset;
	}
	for (int i{ randomNumOfMaita }; i < m_NumberOfEnemies; ++i)
	{
		auto state = Enemy::State::MoveLeft;
		if (i > randomNumOfMaita / 2)
			state = Enemy::State::MoveRight;

		Enemy* enemy = new Enemy{ i,state,Enemy::Type::ZenChan,spawnPos,8,2,16,this,m_PhysicsWorld,BubbleBobbleScene::ENEMY, BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::CHARACTER |  BubbleBobbleScene::BUBBLE };
		this->AddGameObject(enemy);
		m_Listener->AddEnemy(enemy);
		spawnPos.x += spawnOffset;
	}
}

void LVB::BubbleBobbleScene::InitControls()
{
	if (m_Type == GameType::solo)
	{
		InputManager::GetInstance().BindToKeyboard<JumpCommand>(SDL_SCANCODE_SPACE, m_Player1);
		InputManager::GetInstance().BindToKeyboard<MoveLeftCommand>(SDL_SCANCODE_LEFT, m_Player1);
		InputManager::GetInstance().BindToKeyboard<MoveRightCommand>(SDL_SCANCODE_RIGHT, m_Player1);
		InputManager::GetInstance().BindToKeyboard<FireCommand>(SDL_SCANCODE_A, m_Player1);
	}
	else
	{
		InputManager::GetInstance().BindToKeyboard<JumpCommand>(SDL_SCANCODE_SPACE, m_Player2);
		InputManager::GetInstance().BindToKeyboard<MoveLeftCommand>(SDL_SCANCODE_LEFT, m_Player2);
		InputManager::GetInstance().BindToKeyboard<MoveRightCommand>(SDL_SCANCODE_RIGHT, m_Player2);
		InputManager::GetInstance().BindToKeyboard<FireCommand>(SDL_SCANCODE_A, m_Player2);
	}
	InputManager::GetInstance().BindToController<JumpCommand>(LVB::ControllerButton::ButtonA,m_Player1);
	InputManager::GetInstance().BindToController<MoveLeftCommand>(LVB::ControllerButton::DPad_Left, m_Player1);
	InputManager::GetInstance().BindToController<MoveRightCommand>(LVB::ControllerButton::DPad_Right, m_Player1);
	InputManager::GetInstance().BindToController<FireCommand>(LVB::ControllerButton::ButtonB, m_Player1);

}

void LVB::BubbleBobbleScene::CheckLevel(float elapsedSec)
{

	if (m_NumberOfEnemies <= 0)
	{
		m_LevelSwapTimer += elapsedSec;
		if (m_LevelSwapTimer >= m_LevelSwapTime)
		{
			if (m_LevelNumber + 1 == 3)
			{
				SceneManager::GetInstance().SetActiveGameScene("VictoryScene");
				return;
			}
			LoadNewLevel();
			m_LevelSwapTimer = 0.f;
			return;
		}
	}

	if (m_Player1->GetHealth() <= 0)
	{
		SceneManager::GetInstance().SetActiveGameScene("LoseScene");
		return;
	}
	if (m_Player2 != nullptr)
	{
		if (m_Player2->GetHealth() <= 0)
		{
			SceneManager::GetInstance().SetActiveGameScene("LoseScene");
		}
	}
	
}
