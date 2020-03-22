#include "CommandAssignmentScene.h"
#include "InputManager.h"
#include "../Commands/GameCommands.h"
dae::CommandAssignmentScene::CommandAssignmentScene()
	:GameScene("CommandAssignmentScene")
{
	Initialize();
}

void dae::CommandAssignmentScene::Initialize()
{
	JumpCommand* jump = new JumpCommand();
	DuckCommand* duck = new DuckCommand();
	FartCommand* fart = new FartCommand();
	FireCommand* fire = new FireCommand();
	InputManager::GetInstance().BindToController(dae::ControllerButton::ButtonA, jump);
	InputManager::GetInstance().BindToController(dae::ControllerButton::ButtonB, duck);
	InputManager::GetInstance().BindToController(dae::ControllerButton::ButtonX, fart);
	InputManager::GetInstance().BindToController(dae::ControllerButton::ButtonY, fire);
}

void dae::CommandAssignmentScene::Update(float)
{
	InputManager::GetInstance().HandleInput();
}

void dae::CommandAssignmentScene::Render()
{
}
