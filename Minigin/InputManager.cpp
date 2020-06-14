#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool LVB::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	
	DWORD result = XInputGetState(0, &m_CurrentState);
	if (result != ERROR_SUCCESS)
		m_ControllerCheck = false;
	m_CurrentKeyState = SDL_GetKeyboardState(nullptr);
	
	SDL_Event e;
	m_HasClicked = false;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
			m_HasClicked = true;
			m_MouseX = e.button.x;
			m_MouseY = e.button.y;
		}

	}

	return true;
}

const std::vector<LVB::Command*>& LVB::InputManager::HandleInput() const
{
	static std::vector<Command*> commands;
	commands.clear();
	if (m_ControllerCheck)
	{
		for (const auto& button : m_ControllerControls)
		{
			if (m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button.first))
				commands.push_back(button.second);
		}
	}
	for (const auto& key : m_KeyboardControls)
	{
		if (m_CurrentKeyState[key.first])
			commands.push_back(key.second);
	}
	return commands;
}

void LVB::InputManager::BindToKeyboard(SDL_Scancode key, Command* c)
{
	m_KeyboardControls.emplace(key, c);
}

void LVB::InputManager::BindToController(ControllerButton button, Command* c)
{
	m_ControllerControls.emplace(button, c);
}

LVB::Command* LVB::InputManager::UnbindKeyboard(SDL_Scancode key)
{
	Command* c{};
	auto it = m_KeyboardControls.find(key);
	if (it == m_KeyboardControls.end())
		return nullptr;
	c = it->second;
	m_KeyboardControls.erase(it);
	return c;
}

LVB::Command* LVB::InputManager::UnbindController(ControllerButton button)
{
	Command* c{};
	auto it = m_ControllerControls.find(button);
	if (it == m_ControllerControls.end())
		return nullptr;
	c = it->second;
	m_ControllerControls.erase(it);
	return c;
}

void LVB::InputManager::RebindKeyboard(SDL_Scancode oldKey, SDL_Scancode newKey)
{
	BindToKeyboard(newKey, UnbindKeyboard(oldKey));
}

void LVB::InputManager::RebindController(ControllerButton oldKey, ControllerButton newKey)
{
	BindToController(newKey, UnbindController(oldKey));
}

LVB::InputManager::~InputManager()
{
	for (const auto& button : m_ControllerControls)
	{
		delete button.second;
	}
	for (const auto& key : m_KeyboardControls)
	{
		delete key.second;
	}
}

