#pragma once

#include "Rendering/API/RenderableObject.h"

namespace Alpha {
	class OpenGL_RenderableObject : public RenderableObject{
	public:
		OpenGL_RenderableObject();
		OpenGL_RenderableObject(Reference<VertexBuffer>& vbo, Reference<IndexBuffer>& ibo);
		OpenGL_RenderableObject(Reference<IndexBuffer>& ibo);
		~OpenGL_RenderableObject();

		virtual void Bind() const override;

		virtual void AddVertexBuffer(Reference<VertexBuffer>& vbo) override;
		virtual const Reference<VertexBuffer>& RetriveVertexBuffer() const override;

		virtual void SetIndexBuffer(Reference<IndexBuffer>& ibo) override;

		virtual const Reference<IndexBuffer>& GetIndexBuffer() const override;

		void ApplyLayout(const BufferLayout& layout);
	private:
		uint32_t m_VaoID = 0;

		Reference<VertexBuffer> m_VertexBuffer;
		Reference<IndexBuffer> m_IndexBuffer;

	};
}