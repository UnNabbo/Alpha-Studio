#include "UniformBuffer.h"

#include "Platform/OpenGL/OpenGL_UniformBuffer.h"

namespace Alpha {
	Reference<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		return MakeReference<OpenGL_UniformBuffer>(size, binding);
	}
}