#pragma once
#include "Command.h"
class FireCommand : public Command
{
public:
	virtual void Execute() override;
};

class DuckCommand : public Command
{
public:
	virtual void Execute() override;
};

class JumpCommand : public Command
{
public:
	virtual void Execute() override;
};

class FartCommand : public Command
{
public:
	virtual void Execute() override;
};
