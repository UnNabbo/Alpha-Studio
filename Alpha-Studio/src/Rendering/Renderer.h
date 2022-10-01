#pragma once

#include "Core/Core.h"

#include "RenderingAPI.h"

namespace Alpha {
	class RenderableObject;

	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		static void ResizeWindow();
		static void Draw(Reference<RenderableObject>& object);
		static API GetCurrentAPI();
		static void Clear();
		static void Clear(int r, int g, int b);
	};
}