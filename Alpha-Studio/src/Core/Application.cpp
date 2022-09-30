#include "Application.h"

#include "Core/Window/Window.h"

#include "Rendering/API/RenderableObject.h"

#include "glad/glad.h"
namespace Alpha 
{
	inline Application* s_App = 0;

	Application::Application() {
		if (s_App) {};
		s_App = this;
		Log::Init();

		m_Window = Window::Create();
	}

	void Application::OnStart(){
		
	}

	void Application::OnUpdate(){

	}

	void Application::Run(){
		OnStart();


		while (m_Window->ShouldClose()) {
			m_Window->NewFrame();
			

			OnUpdate();
		}
	}

	Application::~Application() {

	}

}