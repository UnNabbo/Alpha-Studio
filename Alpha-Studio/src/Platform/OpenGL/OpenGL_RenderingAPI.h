#pragma once

#include "Core/Core.h"

#include "Rendering/RenderingAPI.h"

namespace Alpha {
	class OpenGL_RenderingAPI : public RenderingAPI {
	public:
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void ResizeWindow() override;
		virtual void Draw(Reference<RenderableObject>& object) override;

		virtual void Clear() override;
		virtual void Clear(int r, int g, int b) override;
	};
}