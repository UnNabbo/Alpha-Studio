#pragma once

#include "Core/Core.h"

#include "RenderingAPI.h"

namespace Alpha {
	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		static void ResizeWindow(int width, int height);

		static void Begin(EditorCamera& cam);

		static void Draw(Reference<RenderableObject>& object);

		static void End();

		static API GetCurrentAPI();
		static void Clear();
		static void SetClearColor(int r, int g, int b);
	};
}