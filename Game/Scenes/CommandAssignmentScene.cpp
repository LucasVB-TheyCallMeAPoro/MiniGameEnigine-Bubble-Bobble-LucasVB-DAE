#include "CommandAssignmentScene.h"
#include "InputManager.h"
#include "../Commands/GameCommands.h"
LVB::CommandAssignmentScene::CommandAssignmentScene()
	:GameScene("CommandAssignmentScene")
{
	Initialize();
}

void LVB::CommandAssignmentScene::Initialize()
{
	JumpCommand* jump = new JumpCommand();
	DuckCommand* duck = new DuckCommand();
	FartCommand* fart = new FartCommand();
	FireCommand* fire = new FireCommand();
	InputManager::GetInstance().BindToController<JumpCommand>(LVB::ControllerButton::ButtonA);
	InputManager::GetInstance().BindToController<DuckCommand>(LVB::ControllerButton::ButtonB);
	InputManager::GetInstance().BindToController<FartCommand>(LVB::ControllerButton::ButtonX);
	InputManager::GetInstance().BindToKeyboard<FireCommand>(SDL_SCANCODE_A);
}

void LVB::CommandAssignmentScene::Update(float)
{
	InputManager::GetInstance().HandleInput();
}

void LVB::CommandAssignmentScene::Render() const
{
}
