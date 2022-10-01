#include "OpenGL_Buffers.h"

#include "glad/glad.h"

namespace Alpha {
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(void* data, size_t size) : m_Size(size) {
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(size_t size) : m_Size(size) {
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
	}
	OpenGL_VertexBuffer::~OpenGL_VertexBuffer() {
		glDeleteBuffers(1, &m_ID);
	}
	void OpenGL_VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}
	void OpenGL_VertexBuffer::SetData(const void* data, size_t size, bool overwrite)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		if (overwrite) {
			void* mem = malloc(m_Size);
			memset(mem, 0, m_Size);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, mem);

		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t* data, size_t size){
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(size_t size){
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}

	OpenGL_IndexBuffer::~OpenGL_IndexBuffer(){
		glDeleteBuffers(1, &m_ID);
	}

	uint32_t OpenGL_IndexBuffer::GetCount()
	{
		return m_Size / sizeof(uint32_t);
	}

	void OpenGL_IndexBuffer::Bind(){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

	}
	void OpenGL_IndexBuffer::SetData(uint32_t* data, size_t size){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}