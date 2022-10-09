#pragma once

#include "Input/Keycode.h"

#include "glm/glm.hpp"

namespace Alpha {
	class Input {
	public:
		static bool GetKey(Keycode key);
		static void LockCursor(bool state);

		static bool GetMouseButton(MouseButton key);
		static bool GetKeyUp(Keycode key);
		static bool GetMouseButtonUp(MouseButton key);
		static bool GetKeyDown(Keycode key);
		static bool GetMouseButtonDown(MouseButton key);
		static glm::vec2 GetMousePos();
	};
}