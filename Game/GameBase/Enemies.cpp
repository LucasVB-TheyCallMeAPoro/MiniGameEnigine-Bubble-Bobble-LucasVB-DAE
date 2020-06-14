#include "Enemies.h"
#include "Box2D.h"
#include "Spritesheet.h"
#include "Texture2D.h"
#include "Transform.h"
#include <iostream>
#include "GameScene.h"
#include "../Scenes/BubbleBobbleScene.h"
#include "ContactListener.h"
#include "Pickup.h"
#include "Boulder.h"

Enemy::Enemy(int id,State state,Type type, glm::vec2 spawnPos, int columnCount, int rowCount, int TotalRowCount, LVB::GameScene* scene, b2World* world, unsigned short categoryMask, unsigned short maskBits)
	:m_Type{type}
	, m_PhysicsWorld{world}
	,m_Scene{scene}
	,m_AnimTime{0}
	,m_JumpForce{-70}
	,m_MoveSpeed{30}
	,m_State{state}
, m_PrevState{ state }
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);

	m_RigidBody = world->CreateBody(&bodyDef);
	m_RigidBody->SetFixedRotation(true);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(7, 8);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = categoryMask;
	fixtureDef.filter.maskBits = maskBits;
	fixtureDef.userData = this;
	m_RigidBody->CreateFixture(&fixtureDef);

	m_RigidBody->SetSleepingAllowed(false);
	m_RigidBody->SetAwake(true);

	//foot sensor
	dynamicBox.SetAsBox(4, 2, b2Vec2(0, 8), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_RigidBody->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)footSensorFixture);

	m_RigidBody->SetUserData((void*)this);
	SetTexture("BBSprites/Sprites0.png");
	int spriteHeight = GetTexture()->GetHeight() / TotalRowCount;
	SetSprite(glm::ivec2(0, 0 + static_cast<unsigned int>(m_Type) * spriteHeight * 2), GetTexture()->GetWidth() / columnCount, spriteHeight, columnCount, rowCount);
}

Enemy::~Enemy()
{
}

void Enemy::HitWall()
{
	if (m_SwapTimer < m_SwapTime)
		return;

	m_SwapTimer = 0.f;
	if (m_State == State::MoveLeft)
	{
		m_State = State::MoveRight;
		
		return;
	}
		
	if (m_State == State::MoveRight)
		m_State = State::MoveLeft;

	if(m_State == State::Attacking)
		 m_State = State::MoveLeft;

}


b2Fixture* Enemy::GetRigidBodyFixture()
{
	return m_RigidBody->GetFixtureList()->GetNext();
}

b2Fixture* Enemy::GetFootSensor()
{
	return m_RigidBody->GetFixtureList();
}

void Enemy::IncrementFootCount()
{
	m_FootContactCount++;
}

void Enemy::DecrementFootCount()
{
	if (m_FootContactCount - 1 < 0)
		m_FootContactCount = 0;
	m_FootContactCount--;
}

void Enemy::HitByBubble()
{
	m_State = State::InBubble;
}

void Enemy::Kill()
{
	m_State = State::Dead;
}

void Enemy::BubbleExpire()
{
	m_State = State::MoveLeft;
	m_RigidBody->SetEnabled(true);
	m_RigidBody->SetTransform({ this->GetTransform()->GetPosition().x,this->GetTransform()->GetPosition().y }, 0);
}



void Enemy::Render() const
{
	
}

void Enemy::Update(float elapsedSec)
{
	if (m_State == State::Dead)
	{
		Destroy();
		return;
	}

	if (m_State == State::InBubble)
	{
		m_RigidBody->SetEnabled(false);
	}
	else
		CheckSeePlayers();

	if (m_FootContactCount > 0)
	{
		switch (m_State)
		{
		case Enemy::MoveLeft:
			MoveLeftBehavior(elapsedSec);
			break;
		case Enemy::MoveRight:
			MoveRightBehavior(elapsedSec);
			break;
		case Enemy::Attacking:
			AttackBehavior(elapsedSec);
			break;
		default:
			break;
		}

	}

	if(m_State != State::InBubble)
	{
		auto rigPos = m_RigidBody->GetTransform();
		this->GetTransform()->SetPosition(rigPos.p.x, rigPos.p.y, 0);
	}
	m_SwapTimer += elapsedSec;

	if(m_State != State::Attacking || m_State != State::InBubble)
		m_PrevState = m_State;
	UpdateSprite(elapsedSec);
}

void Enemy::MoveLeftBehavior(float elapsedSec)
{
	
	m_RigidBody->SetLinearVelocity({ -m_MoveSpeed, m_RigidBody->GetLinearVelocity().y });

}

void Enemy::MoveRightBehavior(float elapsedSec)
{
	m_RigidBody->SetLinearVelocity({ m_MoveSpeed, m_RigidBody->GetLinearVelocity().y });
}

void Enemy::AttackBehavior(float elapsedSec)
{
	switch (m_Type)
	{
	case Enemy::ZenChan:
		if (m_PrevState == State::MoveLeft)
			m_RigidBody->SetLinearVelocity({ -m_MoveSpeed * 3,0 });
		else
			m_RigidBody->SetLinearVelocity({ m_MoveSpeed * 3,0 });

		m_AttackTimer += elapsedSec;
		if (m_AttackTime >= m_AnimTime)
		{
			m_AttackTimer = 0;
			m_State = m_PrevState;
		}
		break;
	case Enemy::Maita:
		if (m_PrevState == State::MoveLeft)
		{
			m_AttackTimer += elapsedSec;
			if (m_AttackTime >= m_AnimTime)
			{
				m_AttackTimer = 0;
				return;
			}
			Boulder* b = new Boulder(m_PhysicsWorld, { m_RigidBody->GetTransform().p.x,m_RigidBody->GetTransform().p.y }, m_Scene, m_MoveSpeed * 2);
			m_Scene->AddGameObject(b);
			m_State = m_PrevState;
		}
		else
		{
			m_AttackTimer += elapsedSec;
			if (m_AttackTime >= m_AnimTime)
			{
				m_AttackTimer = 0;
				return;
			}
			Boulder* b = new Boulder(m_PhysicsWorld, { m_RigidBody->GetTransform().p.x,m_RigidBody->GetTransform().p.y }, m_Scene, -m_MoveSpeed * 2);
			m_Scene->AddGameObject(b);
			m_State = m_PrevState;
		}
		break;
	}	
}

void Enemy::UpdateSprite(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= (1.f / this->GetSprite()->GetSpriteSheet()->GetColumnCount()))
	{
		m_AnimTime = 0;

		int idx = (this->GetSprite()->GetIndex() + 1) % 8;
		switch (m_PrevState)
		{
		case Enemy::State::MoveRight:
			this->GetSprite()->SetIndex(idx);
			break;
		case Enemy::State::MoveLeft:
			idx += 8;
			this->GetSprite()->SetIndex(idx);
			break;
		}
	}
}

void Enemy::Destroy()
{
	PickUp* p{};
	switch (m_Type)
	{
	case Enemy::ZenChan:
	{
		p = new PickUp{ m_PhysicsWorld, glm::vec2{ this->GetTransform()->GetPosition().x,this->GetTransform()->GetPosition().y }, m_Scene,PickUp::Type::melon };
	}
		break;
	case Enemy::Maita:
		p = new PickUp{ m_PhysicsWorld, glm::vec2{ this->GetTransform()->GetPosition().x,this->GetTransform()->GetPosition().y }, m_Scene,PickUp::Type::fries };
		break;
	}
	m_Scene->AddGameObject(p);
	auto s = reinterpret_cast<LVB::BubbleBobbleScene*>(m_Scene);
	s->GetListener()->RemoveEnemy(this);
	s->EnemyKilled();
	m_PhysicsWorld->DestroyBody(m_RigidBody);
	m_Scene->RemoveGameObject(this);
}

void Enemy::CheckSeePlayers()
{
	b2RayCastInput ray{};
	ray.p1 = m_RigidBody->GetTransform().p;
	ray.p2 = ray.p1;
	if (m_PrevState == State::MoveLeft)
		ray.p2.x -= 1;
	else
		ray.p2.x += 1;

	ray.maxFraction = m_ViewRange;

	b2RayCastOutput output{};

	auto s = reinterpret_cast<LVB::BubbleBobbleScene*>(m_Scene);

	switch (s->GetType())
	{
	case LVB::BubbleBobbleScene::GameType::solo:
		if (s->GetPlayer1()->GetBody()->RayCast(&output, ray, 0))
			m_State = State::Attacking;
		break;
	case LVB::BubbleBobbleScene::GameType::coop:
		if (s->GetPlayer1()->GetBody()->RayCast(&output, ray, 0))
			m_State = State::Attacking;
		if(s->GetPlayer2()->GetBody()->RayCast(&output, ray, 0))
			m_State = State::Attacking;
		break;
	}	
	
}
