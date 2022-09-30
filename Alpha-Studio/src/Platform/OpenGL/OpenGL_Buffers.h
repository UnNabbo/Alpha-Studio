#pragma once

#include "Rendering/API/Buffer.h"

namespace Alpha {
	class OpenGL_VertexBuffer : public VertexBuffer {
	public:
		OpenGL_VertexBuffer(void* data, size_t Data);
		OpenGL_VertexBuffer(size_t Data);
		~OpenGL_VertexBuffer();

		virtual void Bind() override;
		virtual void SetData(const void* data, size_t Data, bool overwrite = false) override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		uint32_t m_ID = 0;
		uint32_t m_Size;
		BufferLayout m_Layout = {};
	};

	class OpenGL_IndexBuffer : public IndexBuffer {
	public:
		OpenGL_IndexBuffer(uint32_t* data, size_t size);
		OpenGL_IndexBuffer(size_t size);
		~OpenGL_IndexBuffer();


		virtual void Bind() override;
		virtual void SetData(uint32_t* data, size_t Data) override;
	private:
		uint32_t m_ID = 0;
		uint32_t m_Size;
	};
}