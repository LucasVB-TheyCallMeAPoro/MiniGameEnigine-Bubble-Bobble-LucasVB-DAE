#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	
	DWORD result = XInputGetState(0, &m_CurrentState);
	if (result != ERROR_SUCCESS)
		m_ControllerCheck = false;
	m_CurrentKeyState = SDL_GetKeyboardState(nullptr);
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

void dae::InputManager::HandleInput() const
{
	if (m_ControllerCheck)
	{
		for (const auto& button : m_ControllerControls)
		{
			if (m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button.first))
				button.second->Execute();
		}
	}
	for (const auto& key : m_KeyboardControls)
	{
		if (m_CurrentKeyState[key.first])
			key.second->Execute();
	}
}

void dae::InputManager::BindToKeyboard(SDL_Scancode key, Command* c)
{
	m_KeyboardControls.emplace(key, c);
}

void dae::InputManager::BindToController(ControllerButton button, Command* c)
{
	m_ControllerControls.emplace(button, c);
}

Command* dae::InputManager::UnbindKeyboard(SDL_Scancode key)
{
	Command* c{};
	auto it = m_KeyboardControls.find(key);
	if (it == m_KeyboardControls.end())
		return nullptr;
	c = it->second;
	m_KeyboardControls.erase(it);
	return c;
}

Command* dae::InputManager::UnbindController(ControllerButton button)
{
	Command* c{};
	auto it = m_ControllerControls.find(button);
	if (it == m_ControllerControls.end())
		return nullptr;
	c = it->second;
	m_ControllerControls.erase(it);
	return c;
}

void dae::InputManager::RebindKeyboard(SDL_Scancode oldKey, SDL_Scancode newKey)
{
	BindToKeyboard(newKey, UnbindKeyboard(oldKey));
}

void dae::InputManager::RebindController(ControllerButton oldKey, ControllerButton newKey)
{
	BindToController(newKey, UnbindController(oldKey));
}

