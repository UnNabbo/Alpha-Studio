#pragma once

#include "Core/Core.h"

namespace Alpha {
	enum API {
		OpenGL = 0,
		Vulkan = 1,
		DirectX = 2,
	};

	class RenderableObject;
	class RendererCommand;
	class EditorCamera;

	class RenderingAPI {
		friend RendererCommand;
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void ResizeWindow(int width, int height) = 0;
		virtual void Draw(Reference<RenderableObject>& object) = 0;

		virtual void Begin(EditorCamera& cam) = 0;
		virtual void End() = 0;

		virtual void Clear() = 0;
		virtual void SetClearColor(int r, int g, int b) = 0;

		static API& GetAPI() { return s_CurrentAPI; };
	protected:
		static Reference<RenderingAPI> Create();
		inline static API s_CurrentAPI = API::OpenGL;

	};
}