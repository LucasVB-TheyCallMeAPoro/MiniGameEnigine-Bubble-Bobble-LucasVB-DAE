#include "GameCommands.h"
#include <iostream>
#include  "Audio.h"
#include "../GameBase/Character.h"

void FireCommand::Execute()
{
	Character* character = reinterpret_cast<Character*>(GetGameObject());
	character->Shoot();
}

void JumpCommand::Execute()
{
	Character* character = reinterpret_cast<Character*>(GetGameObject());
	character->Jump();
}

void MoveLeftCommand::Execute()
{
	Character* character = reinterpret_cast<Character*>(GetGameObject());
	character->MoveLeft();
}

void MoveRightCommand::Execute()
{
	Character* character = reinterpret_cast<Character*>(GetGameObject());
	character->MoveRight();
}

FireCommand::FireCommand(GameObject* go)
	:Command{go}
{
}

JumpCommand::JumpCommand(GameObject* go)
	: Command{ go }
{
}

MoveLeftCommand::MoveLeftCommand(GameObject* go)
	: Command{ go }
{
}

MoveRightCommand::MoveRightCommand(GameObject* go)
	: Command{ go }
{
}
