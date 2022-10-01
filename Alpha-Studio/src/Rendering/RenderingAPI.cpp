#include "RenderingAPI.h"

#include "Platform/OpenGL/OpenGL_RenderingAPI.h"

namespace Alpha {

;
	Reference<RenderingAPI> RenderingAPI::Create()
	{
		return MakeReference<OpenGL_RenderingAPI>();
	}
}