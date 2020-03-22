#include "GameCommands.h"
#include <iostream>
#include  "Audio.h"


void FireCommand::Execute()
{
	std::cout << "I'm shooting!\n";
	ServiceLocator::GetAudio().PlaySound(0);
}

void DuckCommand::Execute()
{
	std::cout << "SSSHHH I'm being sneaky!\n";
	ServiceLocator::GetAudio().PlaySound(1);
}

void JumpCommand::Execute()
{
	std::cout << "Jeej I'm jumping of joy!\n";
	ServiceLocator::GetAudio().PlaySound(2);
}

void FartCommand::Execute()
{
	std::cout << "Oh oh STINKYYYY!\n";
	ServiceLocator::GetAudio().PlaySound(3);
}