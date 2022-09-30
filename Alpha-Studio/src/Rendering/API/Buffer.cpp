#include "Buffer.h"

#include "Platform/OpenGL/OpenGL_Buffers.h"

namespace Alpha {

	Reference<VertexBuffer> VertexBuffer::Create(void* data, size_t size)
	{
		return MakeReference<OpenGL_VertexBuffer>(data, size);
	}

	Reference<VertexBuffer> VertexBuffer::Create(size_t size)
	{
		return MakeReference<OpenGL_VertexBuffer>(size);
	}


	Reference<IndexBuffer> IndexBuffer::Create(uint32_t* data, size_t size)
	{
		return MakeReference<OpenGL_IndexBuffer>(data, size);
	}

	Reference<IndexBuffer> IndexBuffer::Create(size_t size)
	{
		return MakeReference<OpenGL_IndexBuffer>(size);
	}
}