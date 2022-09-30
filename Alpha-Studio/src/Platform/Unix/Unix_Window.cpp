#include "Unix_Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace std {

}

namespace Alpha {

	inline static bool GLFW_init = false;

	Unix_Window::Unix_Window(WindowData data) : m_Data(data) {
		Init();
	}

	void Unix_Window::Init(){
		if (!GLFW_init) {
			GLFW_init = glfwInit();

			ALPHA_ASSERT(GLFW_init, "Could Not Inizilize GLFW");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
		ALPHA_INFO("Creating Window: {} ({}, {})", m_Data.Title, m_Data.Width, m_Data.Height);
		m_NativeWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), 0, 0);

		glfwMakeContextCurrent(m_NativeWindow);

		int GL_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ALPHA_ASSERT(GL_status, "Failed to initialize Glad!");

		ALPHA_INFO("OpenGL Infos:\nVendor: {}\nRenderer: {}\nVersion: {}", (char *)glGetString(GL_VENDOR), (char*)glGetString(GL_RENDERER), (char*)glGetString(GL_VERSION));
		glEnable(GL_DEBUG_OUTPUT);

	}

	Unix_Window::~Unix_Window(){
		ShutDown();
	}

	void Unix_Window::ShutDown(){
		glfwDestroyWindow(m_NativeWindow);
	}

	void Unix_Window::SetCurrent() const {
		glfwMakeContextCurrent(m_NativeWindow);
	}

	bool Unix_Window::ShouldClose() const {
		return !glfwWindowShouldClose(m_NativeWindow);
	}

	void Unix_Window::NewFrame(){
		glfwPollEvents();

		glfwSwapBuffers(m_NativeWindow);
	}

}