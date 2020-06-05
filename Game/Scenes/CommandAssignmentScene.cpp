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
	InputManager::GetInstance().BindToController(LVB::ControllerButton::ButtonA, jump);
	InputManager::GetInstance().BindToController(LVB::ControllerButton::ButtonB, duck);
	InputManager::GetInstance().BindToController(LVB::ControllerButton::ButtonX, fart);
	InputManager::GetInstance().BindToKeyboard(SDL_SCANCODE_A, fire);
}

void LVB::CommandAssignmentScene::Update(float)
{
	InputManager::GetInstance().HandleInput();
}

void LVB::CommandAssignmentScene::Render() const
{
}
