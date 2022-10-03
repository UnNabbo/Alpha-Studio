#pragma once

#include "Core/Core.h"

#include "Input/Input.h"

#include "Rendering/Camera/EditorCamera.h"

#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"

namespace Alpha 
{
	class Window;
	class Application {
	public:

		Application();

		virtual void OnStart();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);

		void Run();

		virtual ~Application();

		static Application& GetApp();
		Reference<Window> GetMainWindow();

	private:	
		Reference<Window> m_Window;
		EditorCamera m_EditorCamera;
		

		bool OnWindowResize(WindowResizeEvent& e);
	};

}

