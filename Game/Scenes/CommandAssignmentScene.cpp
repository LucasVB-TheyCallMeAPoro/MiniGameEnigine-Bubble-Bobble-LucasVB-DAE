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

	FireCommand* fire = new FireCommand();
	InputManager::GetInstance().BindToController<JumpCommand>(LVB::ControllerButton::ButtonA);
	InputManager::GetInstance().BindToKeyboard<FireCommand>(SDL_SCANCODE_A);
}

void LVB::CommandAssignmentScene::Update(float)
{
	InputManager::GetInstance().HandleInput();
}

void LVB::CommandAssignmentScene::Render() const
{
}
