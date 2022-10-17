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

#include "Utility/3DModels/ModelLoader.h"

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

		auto x = ModelLoader::Load("C:/Users/saver.SAVERIO/OneDrive/Desktop/Lucy_3M_O10_20.dxf.dxf");

		float vertices[] = {
			  -0.5f, -0.5f, 0.5f, 1,0, 1,0,0,// left  
			   0.5f, -0.5f, 0.5f, 1,0, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f, 1,0,  1,0,1,// top   

			   0.5f, -0.5f, 0.5f, 1,0, 1,0,0,// left  
			   0.5f, -0.5f, -0.5f, 1,0, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f, 1,0,  1,0,1,// top   


			  -0.5f, -0.5f, -0.5f, 1,0, 1,0,0,// left  
			   0.5f, -0.5f, -0.5f, 1,0, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f, 1,0,  1,0,1,// top   


			  -0.5f, -0.5f, 0.5f, 1,0, 1,0,0,// left  
			  -0.5f, -0.5f, -0.5f, 1,0, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f, 1,0,  1,0,1,// top   

			  -0.5f, -0.5f,  0.5f, 1,0, 1,1,0,// left  
			   0.5f, -0.5f,  0.5f, 1,0, 1,1,0,// left  
			  -0.5f, -0.5f, -0.5f, 1,0, 1,1,0,// left  
			   0.5f, -0.5f, -0.5f, 1,0, 1,1,0,// left  

			 
		};

		uint32_t ind[] = {
			0,1,2,

			2,3,4,

			4,5,6,

			6,7,8,

			9,10,11,

			12,13,14,
		};

		Reference<Shader> shader = Shader::Create("./asset/shaders/Fragment.glsl");
		Reference<VertexBuffer> vbo = VertexBuffer::Create(x.Vertices.data(), x.Vertices.size() * sizeof(struct Vertex));
		vbo->SetLayout({ 
			{ ShaderDataType::Float3, "Pos"},
			{ ShaderDataType::Float3, "Normals"},
			{ ShaderDataType::Float2, "Uvs"},
			{ ShaderDataType::Float3, "Normals"},
			{ ShaderDataType::Float3, "Normals"},

		});
		Reference<IndexBuffer> ibo = IndexBuffer::Create(x.Indicies.data(), x.Indicies.size() * sizeof(uint32_t));
		Reference<RenderableObject> ref = RenderableObject::Create(vbo, ibo);

		shader->Bind();

		RendererCommand::SetClearColor(0.65f, 0.65f, 0.65f);

		while (m_Window->ShouldClose()) {
			m_Window->NewFrame();
			Time::Update();

			for (auto layer : m_LayerStack) {
				layer->OnUpdate();
			}

			Renderer::Begin(m_EditorCamera);
			AssetManager::CheckForUpdates();
			RendererCommand::Clear();
			m_EditorCamera.OnUpdate();
			glDrawElements(GL_TRIANGLES, ref->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

			OnUpdate();
		}
	}

	Application::~Application() {

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