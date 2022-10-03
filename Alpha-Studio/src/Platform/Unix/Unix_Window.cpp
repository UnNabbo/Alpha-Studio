#include "Unix_Window.h"

#include "GLFW/glfw3.h"

#include "Rendering/RenderingContext.h"

#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"

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
		Reference<RenderingContext> Context = RenderingContext::Create();
		Context->Init();
		glfwSetWindowUserPointer(m_NativeWindow, &m_Data);

		glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int keycode, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(keycode, mods, 0);
					data.EventCallback(event); 
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(keycode, mods, 1);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(keycode);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(xpos, ypos);
			data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				MouseButtonPressedEvent event(button, 1);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
			});

		glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(xoffset, yoffset);
			data.EventCallback(event);
			});


		glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;

			data.EventCallback(event);
			});

		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			data.Height = height;
			data.Width = width;
			data.EventCallback(event);
			});


		glfwSetWindowPosCallback(m_NativeWindow, [](GLFWwindow* window, int xpos, int ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMovedEvent event(xpos, ypos);
			data.EventCallback(event);
			});


		glfwSetCharCallback(m_NativeWindow, [](GLFWwindow* window, uint32_t character) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(character);
			data.EventCallback(event);
			});
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

	void Unix_Window::SetEventCallBack(const EventCallbackFn& fn){
		m_Data.EventCallback = fn;
	}

	void Unix_Window::NewFrame(){
		glfwPollEvents();

		glfwSwapBuffers(m_NativeWindow);
	}

}