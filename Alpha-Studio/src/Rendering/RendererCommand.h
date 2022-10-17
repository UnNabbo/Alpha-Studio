#pragma once

#include "RenderingAPI.h"

#include "RenderingAPI.h"

namespace Alpha {
	class RendererCommand {
	public:
		static void Init();
		static void ResizeWindow(int width, int height);
		static void Clear();
		static void SetClearColor(int r, int g, int b);
		static void Shutdown();
		static API GetCurrentAPI();

	private:
		inline static Reference<RenderingAPI> s_RenderingAPI = RenderingAPI::Create();
	};
}