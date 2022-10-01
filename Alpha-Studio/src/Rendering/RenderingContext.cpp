#include "RenderingContext.h"

#include "Platform/OpenGL/OpenGL_RenderingContext.h"

namespace Alpha {
	Reference<RenderingContext> RenderingContext::Create() {
		return MakeReference<OpenGL_RenderingContext>();
	}
}