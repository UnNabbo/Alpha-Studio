#pragma once

#include "Core/Core.h"

#include "RenderingAPI.h"

namespace Alpha {
	class RenderableObject;

	class Renderer_Internal {
	public:
		inline static void Init() {
			s_RenderingAPI->Init();
		}

		inline static void Shutdown() {
			s_RenderingAPI->Shutdown();
		}
		inline static void ResizeWindow() {
			s_RenderingAPI->ResizeWindow();
		}
		inline static void Draw(Reference<RenderableObject>& object) {
			s_RenderingAPI->Draw(object);
		}

		inline static void Clear() {
			s_RenderingAPI->Clear();
		}
		inline static void Clear(int r, int g, int b) {
			s_RenderingAPI->Clear(r,g,b);
		}

	private:
		inline static Reference<RenderingAPI> s_RenderingAPI = RenderingAPI::Create();
	};
}