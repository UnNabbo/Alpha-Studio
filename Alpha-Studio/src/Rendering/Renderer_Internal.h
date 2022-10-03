#pragma once

#include "Core/Core.h"

#include "RenderingAPI.h"

namespace Alpha {

	class Renderer_Internal {
	public:
		inline static void Init() {
			s_RenderingAPI->Init();
		}

		inline static void Shutdown() {
			s_RenderingAPI->Shutdown();
		}
		inline static void ResizeWindow(int width, int height) {
			s_RenderingAPI->ResizeWindow(width, height);
		}
		inline static void Draw(Reference<RenderableObject>& object) {
			s_RenderingAPI->Draw(object);
		}

		inline static void Begin(EditorCamera& cam) {
			s_RenderingAPI->Begin(cam);
		}

		inline static void End() {
			s_RenderingAPI->End();
		}

		inline static void Clear() {
			s_RenderingAPI->Clear();
		}

		inline static void SetClearColor(int r, int g, int b) {
			s_RenderingAPI->SetClearColor(r, g, b);
		}

	private:
		inline static Reference<RenderingAPI> s_RenderingAPI = RenderingAPI::Create();
	};
}