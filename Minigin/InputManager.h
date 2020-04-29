#pragma once
#include <Windows.h>
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include "Command.h"
#include <SDL_scancode.h>
namespace LVB
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		DPad_Left = XINPUT_GAMEPAD_DPAD_LEFT,
		DPad_Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		DPad_Up = XINPUT_GAMEPAD_DPAD_UP,
		DPad_Down = XINPUT_GAMEPAD_DPAD_DOWN,
		LT = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RT = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum KeyState
		{
			keyUp = 1,
			keyDown = 2,
			keyHold = 4,
		};
		bool ProcessInput();
		void HandleInput() const;

		void BindToKeyboard(SDL_Scancode, Command*);
		void BindToController(ControllerButton, Command*);

		Command* UnbindKeyboard(SDL_Scancode);
		Command* UnbindController(ControllerButton);

		void RebindKeyboard(SDL_Scancode oldKey, SDL_Scancode newKey);
		void RebindController(ControllerButton oldKey, ControllerButton newKey);

		~InputManager();
	private:
		XINPUT_STATE m_CurrentState{};
		const UINT8* m_CurrentKeyState;
		std::map<SDL_Scancode, Command*> m_KeyboardControls;
		std::map<ControllerButton, Command*> m_ControllerControls;
		bool m_ControllerCheck = true;
	};

}
