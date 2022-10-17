#include "OpenGL_RenderingAPI.h"

#include "Rendering/Primitive/RenderableObject.h"

#include "glad/glad.h"

#include "Rendering/Primitive/Shader.h"

namespace Alpha {
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         ALPHA_FATAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       ALPHA_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          ALPHA_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: ALPHA_TRACE(message); return;
		}
	}

	void OpenGL_RenderingAPI::Init(){
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		glEnable(GL_DEPTH_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGL_RenderingAPI::Shutdown(){

	}
	void OpenGL_RenderingAPI::ResizeWindow(int width, int height){
		glViewport(0, 0, width, height);
	}
	void OpenGL_RenderingAPI::Draw(Reference<RenderableObject>& object){
		object->Bind();
		glDrawElements(GL_TRIANGLES, object->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGL_RenderingAPI::Begin(EditorCamera& cam){

	}

	void OpenGL_RenderingAPI::End(){

	}
	void OpenGL_RenderingAPI::Clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGL_RenderingAPI::SetClearColor(int r, int g, int b){
		glClearColor(r, g, b, 1.0f);
	}
}