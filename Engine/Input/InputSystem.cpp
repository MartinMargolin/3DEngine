#include "InputSystem.h"

namespace smile
{

	void InputSystem::Startup()
	{
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		keyboardState.resize(numKeys);

		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevKeyboardState = keyboardState;

	
	}

	void InputSystem::Shutdown()
	{
	
	}

	void InputSystem::Update(float dt)
	{
	
		prevKeyboardState = keyboardState;

		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevMouseButtonState = mouseButtonState;
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = glm::vec2{ x, y };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0000] & [0RML]
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0000] & [0RML]
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0000] & [0RML]

	}


	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::IDLE;

		bool keyDown = IsKeyDown(id);
		bool prevKeyDown = IsPreviousKeyDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::HELD : eKeyState::PRESSED ;
		}
		else
			{
			state = (prevKeyDown) ? eKeyState::RELEASED : eKeyState::IDLE ;
			}
			
		return state;
	}

	bool InputSystem::IsKeyDown(int id)
	{
		return keyboardState[id];
	}

	bool InputSystem::IsPreviousKeyDown(int id)
	{
		return prevKeyboardState[id];
	}

	InputSystem::eKeyState InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::IDLE;

		bool keyDown = IsButtonDown(id);
		bool prevKeyDown = IsPreviousButtonDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::HELD : eKeyState::PRESSED;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::RELEASED : eKeyState::IDLE;
		}

		return state;
	}

}
