#pragma once
#include "Command.h"
using namespace LVB;
class FireCommand : public Command
{
public:
	FireCommand(GameObject* go);
	virtual void Execute() override;
};

class JumpCommand : public Command
{
public:
	JumpCommand(GameObject* go);
	virtual void Execute() override;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(GameObject* go);
	virtual void Execute() override;
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(GameObject* go);
	virtual void Execute() override;
};
