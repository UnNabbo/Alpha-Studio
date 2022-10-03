#pragma once

#include "Events.h"

namespace Alpha {
	class  KeyEvent : public Event {
	public:
		inline int GetKeyCode() { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(int keycode)
			: m_keycode(keycode) {
		}

		int m_keycode;
	};

	class  KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int mods, bool held)
			: KeyEvent(keycode), m_mods(mods), m_held(held) {}

		inline bool IsHeld() { return m_held; }
		inline int getMods() { return m_mods; }


		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool m_held;
		int m_mods;
	};

	class  KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class  KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(uint32_t character)
			: KeyEvent(character) {
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

	class  MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int button, bool held)
			: m_button(button), m_held(held) {
			int x = 0;
		}

		inline int GetButton() { return m_button; }

		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		int m_button;
		bool m_held;
	};


	class  MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int button)
			: m_button(button) {}

		inline int GetButton() { return m_button; }

		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		int m_button;
	};

	class  MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() { return m_MouseX; }
		inline float GetY() { return m_MouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_MouseX;
		float m_MouseY;
	};

	class  MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_MouseXoffset(xOffset), m_MouseYoffset(yOffset) {}

		inline float GetXoffnset() { return m_MouseXoffset; }
		inline float GetYoffset() { return m_MouseYoffset; }


		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_MouseXoffset;
		float m_MouseYoffset;

	};

}