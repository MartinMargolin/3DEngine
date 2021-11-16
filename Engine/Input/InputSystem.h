#pragma once
#include "Framework/System.h"
#include "Math/MathTypes.h"
#include <vector>
#include <array>
#include <SDL.h>


namespace smile
{

class InputSystem : public System
{
	public:
		enum class eKeyState 
		{
			IDLE,
			PRESSED,
			HELD,
			RELEASED
		};

		enum class eMouseButton
		{
			LEFT,
			MIDDLE,
			RIGHT
		};
	public:
		// Inherited via System
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

		const glm::vec2& GetMousePosition() { return mousePosition; }
		bool IsButtonDown(int id) { return mouseButtonState[id]; };
		bool IsPreviousButtonDown(int id) { return prevMouseButtonState[id]; };
		eKeyState GetButtonState(int id);

	private: 
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;

		glm::vec2 mousePosition;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;
	};

}