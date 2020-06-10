#include "GameCommands.h"
#include <iostream>
#include  "Audio.h"
#include "../GameBase/Character.h"

void FireCommand::Execute(GameObject* )
{
	//Character* character = reinterpret_cast<Character*>(actor);
	std::cout << "I'm shooting!\n";
	ServiceLocator::GetAudio().PlaySound(0);
}

void DuckCommand::Execute(GameObject* )
{
	std::cout << "SSSHHH I'm being sneaky!\n";
	ServiceLocator::GetAudio().PlaySound(1);
}

void JumpCommand::Execute(GameObject* actor)
{
	Character* character = reinterpret_cast<Character*>(actor);
	character->Jump();
	std::cout << "Jeej I'm jumping of joy!\n";
	ServiceLocator::GetAudio().PlaySound(2);
}

void FartCommand::Execute(GameObject* )
{
	std::cout << "Oh oh STINKYYYY!\n";
	ServiceLocator::GetAudio().PlaySound(3);
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
