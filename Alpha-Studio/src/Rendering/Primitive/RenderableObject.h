#pragma once

#include "Buffer.h"

#include <vector>

namespace Alpha {
	class RenderableObject {
	public:
		virtual void Bind() const = 0;

		virtual void AddVertexBuffer(Reference<VertexBuffer>& vbo) = 0;
		virtual const Reference<VertexBuffer>& RetriveVertexBuffer() const = 0;

		virtual void SetIndexBuffer(Reference<IndexBuffer>& ibo) = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const = 0;

		static Reference<RenderableObject> Create();
		static Reference<RenderableObject> Create(Reference<VertexBuffer>& vbo, Reference<IndexBuffer>& ibo);
		static Reference<RenderableObject> Create(Reference<IndexBuffer>& ibo);
	};
}