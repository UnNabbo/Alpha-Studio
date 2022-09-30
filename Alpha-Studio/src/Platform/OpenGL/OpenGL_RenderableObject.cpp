#include "OpenGL_RenderableObject.h"

#include "glad/glad.h"

namespace Alpha {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Bool:   return GL_BOOL;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        }
    }

    OpenGL_RenderableObject::OpenGL_RenderableObject(){
        glGenVertexArrays(1, &m_VaoID);
        glBindVertexArray(m_VaoID);
    }

    OpenGL_RenderableObject::OpenGL_RenderableObject(Reference<VertexBuffer>& vbo, Reference<IndexBuffer>& ibo) : m_VertexBuffer(vbo), m_IndexBuffer(ibo) {
        glGenVertexArrays(1, &m_VaoID);
        glBindVertexArray(m_VaoID);

        m_VertexBuffer->Bind();
        m_IndexBuffer->Bind();

        ApplyLayout(m_VertexBuffer->GetLayout());

    }

    OpenGL_RenderableObject::OpenGL_RenderableObject(Reference<IndexBuffer>& ibo) : m_IndexBuffer(ibo) {
        glGenVertexArrays(1, &m_VaoID);
        glBindVertexArray(m_VaoID);

        m_IndexBuffer->Bind();
    }

    OpenGL_RenderableObject::~OpenGL_RenderableObject(){
        glDeleteVertexArrays(1, &m_VaoID);
    }

    void OpenGL_RenderableObject::Bind() const{
        glBindVertexArray(m_VaoID);


    }

    void OpenGL_RenderableObject::AddVertexBuffer(Reference<VertexBuffer>& vbo){
        m_VertexBuffer = vbo;
        m_VertexBuffer->Bind();

        ApplyLayout(m_VertexBuffer->GetLayout());
    }

    const Reference<VertexBuffer>& OpenGL_RenderableObject::RetriveVertexBuffer() const{
        return m_VertexBuffer;
    }

    void OpenGL_RenderableObject::ApplyLayout(const BufferLayout& layout){
        uint32_t index = 0;
        auto IterableLayout = layout;
        for (const auto& element : IterableLayout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponetCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized,
                layout.GetStride(),
                (void*)element.Offset);
            index++;
        }
    }

    void OpenGL_RenderableObject::SetIndexBuffer(Reference<IndexBuffer>& ibo){
        m_IndexBuffer = ibo;
    }

    const Reference<IndexBuffer>& OpenGL_RenderableObject::GetIndexBuffer() const{
        return m_IndexBuffer;
    }

}