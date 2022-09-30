#include "Window.h"

#include "Platform/Unix/Unix_Window.h"

namespace Alpha {
	Reference<Window> Window::Create(WindowData data)
	{
		return MakeReference<Unix_Window>(data);
	}
}