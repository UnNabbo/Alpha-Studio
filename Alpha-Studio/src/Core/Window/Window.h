#pragma once

#include <stdint.h>
#include <string>

#include "Core/Core.h"

namespace Alpha {

	struct WindowData {
		std::string Title;
		uint32_t Height, Width;

		WindowData(std::string title = "Window", uint32_t width = 1600, uint32_t height = 900) : Title(title), Height(height), Width(width) {}
	};

	class Window {
	public:

		virtual void* GetNative() const = 0;

		virtual void SetCurrent() const = 0;

		virtual bool ShouldClose() const = 0;

		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetWidth() const = 0;

		virtual void NewFrame() = 0;

		static Reference<Window> Create(WindowData data = WindowData());
	};
}