#include "Application.h"

#include "Utility/Log/Log.h"

namespace Alpha 
{
	inline Application* s_App = 0;

	Application::Application() {
		if (s_App) {};
		s_App = this;
		Log::Init();
	}

	void Application::OnStart(){

	}

	void Application::OnUpdate(){
		ALPHA_TRACE("{}: {}", "sd", 42);
		ALPHA_INFO("{}: {}", "sd", 42);
		ALPHA_WARN("{}: {}", "sd", 42);
		ALPHA_ERROR("{}: {}", "sd", 42);
		ALPHA_FATAL("{}: {}", "sd", 42);

	}

	void Application::Run(){
		OnStart();
		while (true) {
			OnUpdate();
		}
	}

	Application::~Application() {

	}

}