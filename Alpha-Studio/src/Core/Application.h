#pragma once

#include "Core/Core.h"

#include "Input/Input.h"

#include "Rendering/Camera/EditorCamera.h"

#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"

#include "Core/Layer/LayerStack.h"

namespace Alpha 
{
	class Window;
	class Application {
	public:

		Application();

		virtual void OnStart();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);

		inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
		inline void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }
		inline void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }
		inline void PopOverlay(Layer* overlay) { m_LayerStack.PopOverlay(overlay); }

		void Run();

		virtual ~Application();

		static Application& GetApp();
		Reference<Window> GetMainWindow();

	private:	
		Reference<Window> m_Window;
		EditorCamera m_EditorCamera;
		LayerStack m_LayerStack;

		bool OnWindowResize(WindowResizeEvent& e);
	};

}

