#include "OpenGL_RenderingContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Alpha {
	int OpenGL_RenderingContext::Init()
	{
		int GL_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ALPHA_ASSERT(GL_status, "Failed to initialize Glad!");

		ALPHA_INFO("OpenGL Infos:\nVendor: {}\nRenderer: {}\nVersion: {}", (char*)glGetString(GL_VENDOR), (char*)glGetString(GL_RENDERER), (char*)glGetString(GL_VERSION));
		glEnable(GL_DEBUG_OUTPUT);
		return GL_status;
	}
	void OpenGL_RenderingContext::Shutdown()
	{

	}
}