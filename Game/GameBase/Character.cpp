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
Character::Character(Character::Type type, int columnCount, int rowCount, int totalRowCount, b2World* world, const glm::vec2& spawnPos, LVB::GameScene* scene)
	:m_Type{type}
	,m_AnimTime{0.f}
	,m_ColumnCount{columnCount}
	,m_State{ Character::State::moveRight }
	,m_PhysicsWorld{world}
	,m_Scene{scene}
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnPos.x, spawnPos.y);
	
	m_RigidBody = world->CreateBody(&bodyDef);
	m_RigidBody->SetFixedRotation(true);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(8,8);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = (void*)2;
	m_RigidBody->CreateFixture(&fixtureDef);

	m_RigidBody->SetSleepingAllowed(false);
	m_RigidBody->SetAwake(true);

	dynamicBox.SetAsBox(8, 2, b2Vec2(0, 8), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_RigidBody->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)3);
	
	SetTexture("BBSprites/Sprites0.png");
	int spriteHeight = GetTexture()->GetHeight() / totalRowCount;
	SetSprite(glm::ivec2(0, 0 + static_cast<unsigned int>(m_Type) * spriteHeight * 2), GetTexture()->GetWidth() / columnCount, spriteHeight, columnCount, rowCount);

	InitControls();
}

void Character::Shoot()
{
	switch (m_State)
	{
	case Character::moveLeft:
	{
		Bubble* bubble = new Bubble{ m_PhysicsWorld, {this->GetTransform()->GetPosition().x - 30, this->GetTransform()->GetPosition().y + 8} };
		m_Scene->AddGameObject(bubble);
	}
	break;
	case Character::moveRight:
	{
		Bubble* bubble = new Bubble{ m_PhysicsWorld, {this->GetTransform()->GetPosition().x + 30, this->GetTransform()->GetPosition().y + 8} };
		m_Scene->AddGameObject(bubble);
	}
	break;
	}
	

}

void Character::Jump()
{
	if (m_FootContactCount >= 1)
	{
		m_RigidBody->SetLinearVelocity({ m_RigidBody->GetLinearVelocity().x,-70 });
	}
}

void Character::MoveLeft()
{
	m_RigidBody->SetLinearVelocity({ -40,m_RigidBody->GetLinearVelocity().y });
	m_State = Character::State::moveLeft;
}

void Character::MoveRight()
{
	m_RigidBody->SetLinearVelocity({ 40,m_RigidBody->GetLinearVelocity().y });
	m_State = Character::State::moveRight;
}

void Character::Render() const
{
	
}

void Character::Update(float elapsedSec)
{
	Command* command = InputManager::GetInstance().HandleInput();
	if (command != nullptr)
	{
		command->Execute(this);
	}
	else
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
}

void Character::InitControls()
{
	InputManager::GetInstance().BindToController<JumpCommand>(LVB::ControllerButton::ButtonA);
	InputManager::GetInstance().BindToController<MoveLeftCommand>(LVB::ControllerButton::DPad_Left);
	InputManager::GetInstance().BindToController<MoveRightCommand>(LVB::ControllerButton::DPad_Right);
	InputManager::GetInstance().BindToController<FireCommand>(LVB::ControllerButton::ButtonB);
	InputManager::GetInstance().BindToKeyboard<JumpCommand>(SDL_SCANCODE_SPACE);
	InputManager::GetInstance().BindToKeyboard<MoveLeftCommand>(SDL_SCANCODE_LEFT);
	InputManager::GetInstance().BindToKeyboard<MoveRightCommand>(SDL_SCANCODE_RIGHT);
	InputManager::GetInstance().BindToKeyboard<FireCommand>(SDL_SCANCODE_A);
}
