#include "GameCommands.h"
#include <iostream>
#include  "Audio.h"
#include "../GameBase/Character.h"

void FireCommand::Execute(GameObject* actor)
{
	Character* character = reinterpret_cast<Character*>(actor);
	character->Shoot();
}

void DuckCommand::Execute(GameObject*)
{
}

void JumpCommand::Execute(GameObject* actor)
{
	Character* character = reinterpret_cast<Character*>(actor);
	character->Jump();
}

void FartCommand::Execute(GameObject* )
{
}

void MoveLeftCommand::Execute(GameObject* actor)
{
	Character* character = reinterpret_cast<Character*>(actor);
	character->MoveLeft();
}

void MoveRightCommand::Execute(GameObject* actor)
{
	Character* character = reinterpret_cast<Character*>(actor);
	character->MoveRight();
}
