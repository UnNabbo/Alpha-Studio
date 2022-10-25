#include "Application.h"

#include "Core/Window/Window.h"

#include "Rendering/Primitive/RenderableObject.h"

#include "Rendering/Renderer.h"

#include "Rendering/Primitive/Shader.h"

#include "glad/glad.h"

#include "Rendering/Primitive/UniformBuffer.h"

#include "Asset/AssetManager.h"

#include "Utility/Time/Time.h"

#include "Rendering/RendererCommand.h"

#include "Rendering/Primitive/Mesh/Mesh.h"

#include "Rendering/RenderingQueue.h"

#include "Utility/MeshLoader/MeshLoader.h"

#include "Utility/Serialization/Serializer.h"

namespace Alpha 
{



	inline static Application* s_App = 0;

	Application::Application() {
		if (s_App) {};
		s_App = this;
		Log::Init();


	

		m_Window = Window::Create();
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));
		Renderer::Init();
		Time::Init();
	}

	void Application::OnStart(){
		
	}

	void Application::OnUpdate(){

	}

	void Application::OnEvent(Event &e){
		EventsDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		m_EditorCamera.OnEvent(e);

		for (auto layer : m_LayerStack) {
			layer->OnEvent(e);
		}
	}

	void Application::Run(){
		OnStart();

		//auto x = Mesh3D::Create("C:/Users/saver.SAVERIO/OneDrive/Desktop/Lucy_3M_O10_20.dxf.dxf");
		auto x = Mesh3D::Create("C:/Users/saver.SAVERIO/OneDrive/Desktop/Pony_cartoon.obj");

		Reference<Shader> shader = Shader::Create("./asset/shaders/Fragment.glsl");
		
		shader->Bind();
		RendererCommand::SetClearColor(0.65f, 0.65f, 0.65f);

		x->GetRenderableObject()->Bind();

		while (m_Window->ShouldClose()) {
			m_Window->NewFrame();
			Time::Update();

			for (auto layer : m_LayerStack) {
				layer->OnUpdate();
			}

			AssetManager::CheckForUpdates();

			Renderer::Begin(m_EditorCamera);
			RendererCommand::Clear();
			Renderer::Submit(x);
			Renderer::End();

			m_EditorCamera.OnUpdate();


			Renderer::Render();


			OnUpdate();
		}
	}

	Application::~Application() {
		AssetManager::Clear();
	}

	Application& Application::GetApp()
	{
		return *s_App;
	}

	Reference<Window> Application::GetMainWindow()
	{
		return m_Window;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		m_EditorCamera.SetViewportSize(e.GetWidth(), e.GetHeight()); 
		RendererCommand::ResizeWindow(e.GetWidth(), e.GetHeight());
		return false;
	}

}