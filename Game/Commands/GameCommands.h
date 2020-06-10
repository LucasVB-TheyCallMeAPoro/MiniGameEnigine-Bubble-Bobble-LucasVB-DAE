#pragma once
#include "Command.h"
using namespace LVB;
class FireCommand : public Command
{
public:
	virtual void Execute(GameObject* actor) override;
};

class DuckCommand : public Command
{
public:
	virtual void Execute(GameObject* actor) override;
};

class JumpCommand : public Command
{
public:
	virtual void Execute(GameObject* actor) override;
};

class FartCommand : public Command
{
public:
	virtual void Execute(GameObject* actor) override;
};

class MoveLeftCommand : public Command
{
public:
	virtual void Execute(GameObject* actor) override;
};

class MoveRightCommand : public Command
{
public:
	virtual void Execute(GameObject* actor) override;
};