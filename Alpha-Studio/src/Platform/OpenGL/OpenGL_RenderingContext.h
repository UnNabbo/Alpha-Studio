#pragma once

#include "Core/Core.h"

#include "Rendering/RenderingContext.h"

namespace Alpha {
	class OpenGL_RenderingContext : public RenderingContext{
	public:
		virtual int Init() override;
		virtual void Shutdown() override;
	};
}