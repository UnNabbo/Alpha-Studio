#include "RenderableObject.h"

#include "Platform/OpenGL/OpenGL_RenderableObject.h"

namespace Alpha {

	Reference<RenderableObject> RenderableObject::Create()
	{
		return MakeReference<OpenGL_RenderableObject>();
	}

	Reference<RenderableObject> RenderableObject::Create(Reference<VertexBuffer>& vbo, Reference<IndexBuffer>& ibo)
	{
		return MakeReference<OpenGL_RenderableObject>(vbo, ibo);
	}

	Reference<RenderableObject> RenderableObject::Create(Reference<IndexBuffer>& ibo)
	{
		return MakeReference<OpenGL_RenderableObject>(ibo);
	}
}