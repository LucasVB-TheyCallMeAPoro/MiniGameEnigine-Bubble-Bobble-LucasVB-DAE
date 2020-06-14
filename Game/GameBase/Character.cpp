#include "Character.h"
#include "ResourceManager.h"
#include <Structs.h>
#include "Texture2D.h"
#include "SDL.h"
#include "Spritesheet.h"
#include "Box2D.h"
#include "Transform.h"
#include <iostream>
#include "InputManager.h"
#include "../Commands/GameCommands.h"
#include "Bubble.h"
#include "GameScene.h"
#include "../Scenes/BubbleBobbleScene.h"
#include "Boulder.h"
Character::Character(Player p,Character::Type type, int columnCount, int rowCount, int totalRowCount, b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene, unsigned short categoryMask, unsigned short maskBits)
	:m_Type{type}
	,m_AnimTime{0.f}
	,m_ColumnCount{columnCount}
	,m_State{ Character::State::moveRight }
	,m_PhysicsWorld{world}
	,m_Scene{scene}
	,m_OnChangeScore{}
	,m_OnChangeHealth{}
	,m_Health{4}
	,m_Score{0}
	,m_Shot{false}
	,m_JumpForce{-70}
	,m_MoveSpeed{60}
	,m_SpawnPosition{spawnPos}
	, m_Jumped{ false }
	,m_TotalJumpTime{1.f}
	,m_JumpTime{0}
	,m_Player{p}
	, m_SensorName{nullptr}
{

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);
	
	m_RigidBody = world->CreateBody(&bodyDef);
	m_RigidBody->SetFixedRotation(true);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(7,8);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = categoryMask;
	fixtureDef.filter.maskBits = maskBits;
	m_RigidBody->CreateFixture(&fixtureDef);

	m_RigidBody->SetSleepingAllowed(false);
	m_RigidBody->SetAwake(true);

	//foot sensor
	dynamicBox.SetAsBox(4, 2, b2Vec2(0, 8), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_RigidBody->CreateFixture(&fixtureDef);

	footSensorFixture->SetUserData((void*)footSensorFixture);
	
	m_RigidBody->SetUserData((void*)m_RigidBody);
	SetTexture("BBSprites/Sprites0.png");
	int spriteHeight = GetTexture()->GetHeight() / totalRowCount;
	SetSprite(glm::ivec2(0, 0 + static_cast<unsigned int>(m_Type) * spriteHeight * 2), GetTexture()->GetWidth() / columnCount, spriteHeight, columnCount, rowCount);

}

Character::~Character()
{
	delete m_SensorName;
}

b2Fixture* Character::GetBody() const
{
	return m_RigidBody->GetFixtureList()->GetNext();
}

b2Fixture* Character::GetFootSensor() const
{
	return m_RigidBody->GetFixtureList();
}

void Character::Shoot()
{
	if (m_Shot)
		return; 

	switch (m_Type)
	{
	case Character::Maita:
		break;
	default:
	{
		glm::vec2 spawnOffset{ 30,8 };
		switch (m_State)
		{
		case Character::moveLeft:
		{
			Bubble* bubble = new Bubble{ m_PhysicsWorld, {this->GetTransform()->GetPosition().x - spawnOffset.x, this->GetTransform()->GetPosition().y + spawnOffset.y},m_Scene };
			m_Scene->AddGameObject(bubble);
		}
		break;
		case Character::moveRight:
		{
			Bubble* bubble = new Bubble{ m_PhysicsWorld, {this->GetTransform()->GetPosition().x + spawnOffset.x, this->GetTransform()->GetPosition().y + spawnOffset.y}, m_Scene };
			m_Scene->AddGameObject(bubble);
		}
		break;
		}
	}
		break;
	}
	
	m_Shot = true;

}

void Character::Jump()
{
	if (m_FootContactCount >= 1 && !m_Jumped)
	{
		m_RigidBody->SetLinearVelocity({ m_RigidBody->GetLinearVelocity().x,m_JumpForce });
		b2Filter filter = m_RigidBody->GetFixtureList()->GetNext()->GetFilterData();

		//filter.maskBits &= ~LVB::BubbleBobbleScene::entityType::PLATFORM;
		filter.maskBits = BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::ENEMY;
		
		m_RigidBody->GetFixtureList()->GetNext()->SetFilterData(filter);
		m_Jumped = true;
	}
}

void Character::MoveLeft()
{
	m_RigidBody->SetLinearVelocity({ -m_MoveSpeed,m_RigidBody->GetLinearVelocity().y });
	if (m_State != Character::State::moveLeft)
	{
		m_State = Character::State::moveLeft;
	}
}

void Character::MoveRight()
{
	m_RigidBody->SetLinearVelocity({ m_MoveSpeed,m_RigidBody->GetLinearVelocity().y });

	if (m_State != Character::State::moveRight)
	{
		m_State = Character::State::moveRight;
	}
	
}

void Character::TakeDamage()
{
	if (!m_Hit)
	{
		m_Health -= 1;
		m_OnChangeHealth.Notify(m_Health);
		m_Hit = true;
	}

}

void Character::AddScore(int amount)
{
	m_Score += amount;
	m_OnChangeScore.Notify(m_Score);
}

void Character::NotifyUI()
{
	m_OnChangeHealth.Notify(m_Health);
	m_OnChangeScore.Notify(m_Score);
}

void Character::SetToSpawnPos()
{
	this->GetTransform()->SetPosition(m_SpawnPosition.x, m_SpawnPosition.y, 0);
	m_RigidBody->SetTransform({ m_SpawnPosition.x,m_SpawnPosition.y }, 0);
}

void Character::IncrementFootCount()
{
	m_FootContactCount++;
}

void Character::DecrementFootCount()
{
	if (m_FootContactCount - 1 < 0)
		m_FootContactCount = 0;
	m_FootContactCount--;
}

void Character::HitByBubble(const glm::vec3& pos, float yspeed, float time)
{
	m_State = State::bubble;
	m_HitBubble = true;
	m_BubblePos = { pos.x,pos.y };
	m_UpwardsSpeed = yspeed;
	m_FloatingDuration = time;
}

void Character::Render() const
{
	
}

void Character::Update(float elapsedSec)
{
	if (m_Jumped)
	{
		m_JumpTime += elapsedSec;
		if (m_JumpTime >= m_TotalJumpTime)
		{
			m_JumpTime = 0.f;
			m_Jumped = false;
			b2Filter filter = m_RigidBody->GetFixtureList()->GetNext()->GetFilterData();

			filter.maskBits = BubbleBobbleScene::BOUNDARY | BubbleBobbleScene::PLATFORM | BubbleBobbleScene::ENEMY;

			m_RigidBody->GetFixtureList()->GetNext()->SetFilterData(filter);
		}
	}
	if (m_Hit)
	{
		m_HitTimer += elapsedSec;
		if (m_HitTimer >= m_SaveTime)
		{
			m_Hit = false;
			m_HitTimer = 0;
		}
	}
	const std::vector<Command*>& commands = InputManager::GetInstance().HandleInput();
	bool commandCheck{ false };
	for (int i{ 0 }; i < commands.size(); ++i)
	{
		if (commands[i]->GetGameObject() == this)
		{
			commands[i]->Execute();
			commandCheck = true;
		}
	}
	if(!commandCheck)
	{
		m_RigidBody->SetLinearVelocity({ 0,m_RigidBody->GetLinearVelocity().y });
	}

	m_AnimTime += elapsedSec;
	if (m_AnimTime >= (1.f / this->GetSprite()->GetSpriteSheet()->GetColumnCount()))
	{
		m_AnimTime = 0;
		
		int idx = (this->GetSprite()->GetIndex() + 1) % 8;
		switch (m_State)
		{
		case Character::State::moveRight:
			this->GetSprite()->SetIndex(idx);
			break;
		case Character::State::moveLeft:
			idx += 8;
			this->GetSprite()->SetIndex(idx);
			break;
		}
	}
	auto rigPos = m_RigidBody->GetTransform();
	this->GetTransform()->SetPosition(rigPos.p.x, rigPos.p.y, 0);

	if (m_Shot)
	{
		m_BubbleCooldownTimer += elapsedSec;
		if (m_BubbleCooldownTimer >= m_BubbleCooldown)
		{
			m_Shot = false;
			m_BubbleCooldownTimer = 0.f;
		}
	}

	//214 is world bottom
	if (this->GetTransform()->GetPosition().y > 214)
	{
		SpawnAtTop();
	}
}

void Character::SpawnAtTop()
{
	this->GetTransform()->SetPosition(this->GetTransform()->GetPosition().x, 0, 0);
	m_RigidBody->SetTransform({ this->GetTransform()->GetPosition().x ,this->GetTransform()->GetPosition().y }, 0);
}
