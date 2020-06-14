#pragma once
#include <Windows.h>
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include "Command.h"
#include <SDL_scancode.h>
#include <type_traits>
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
		const std::vector<Command*>& HandleInput() const;

		Command* UnbindKeyboard(SDL_Scancode);
		Command* UnbindController(ControllerButton);

		void RebindKeyboard(SDL_Scancode oldKey, SDL_Scancode newKey);
		void RebindController(ControllerButton oldKey, ControllerButton newKey);

		~InputManager();

		template <typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Command, T>, int> = 0>
		void BindToKeyboard(SDL_Scancode key, Args&&... args)
		{
			Command* c = new T(std::forward<Args>(args)...);
			BindToKeyboard(key, c);
		}
		template <typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Command, T>, int> = 0>
		void  BindToController(ControllerButton button, Args&&... args)
		{
			Command* c = new T(std::forward<Args>(args)...);
			BindToController(button, c);
		}
		bool GetClick(int* x, int* y) const
		{
			*x = m_MouseX;
			*y = m_MouseY;
			return m_HasClicked;
		}
	private:
		XINPUT_STATE m_CurrentState{};
		const UINT8* m_CurrentKeyState;
		std::map<SDL_Scancode, Command*> m_KeyboardControls;
		std::map<ControllerButton, Command*> m_ControllerControls;
		bool m_ControllerCheck = true;

		int m_MouseX;
		int m_MouseY;
		bool m_HasClicked= false;
		void BindToKeyboard(SDL_Scancode, Command*);
		void BindToController(ControllerButton, Command*);
	};

}
