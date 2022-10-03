#pragma once

#include "Core/Core.h"

#include "Rendering/RenderingAPI.h"

namespace Alpha {
	class OpenGL_RenderingAPI : public RenderingAPI {
	public:
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void ResizeWindow(int width, int height) override;
		virtual void Draw(Reference<RenderableObject>& object) override;
		virtual void Begin(EditorCamera& cam) override;
		virtual void End() override;

		virtual void Clear() override;
		virtual void SetClearColor(int r, int g, int b) override;
	};
}