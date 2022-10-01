#pragma once

#include "Core/Core.h"

namespace Alpha {
	class RenderingContext {
	public:

		static Reference<RenderingContext> Create();
		virtual int Init() = 0;
		virtual void Shutdown() = 0;
	};
}