#include "Application.h"

#include "Core/Window/Window.h"

#include "Rendering/API/RenderableObject.h"

#include "Rendering/Renderer.h"

#include "Rendering/API/Shader.h"

#include "glad/glad.h"


#include "Rendering/API/UniformBuffer.h"

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

	}

	void Application::OnStart(){
		
	}

	void Application::OnUpdate(){

	}

	void Application::OnEvent(Event &e){
		EventsDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		m_EditorCamera.OnEvent(e);
	}

	void Application::Run(){
		OnStart();

		float vertices[] = {
			  -0.5f, -0.5f, 0.5f, 1,0,0,// left  
			   0.5f, -0.5f, 0.5f, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f,  1,0,1,// top   

			   0.5f, -0.5f, 0.5f, 1,0,0,// left  
			   0.5f, -0.5f, -0.5f, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f,  1,0,1,// top   


			  -0.5f, -0.5f, -0.5f, 1,0,0,// left  
			   0.5f, -0.5f, -0.5f, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f,  1,0,1,// top   


			  -0.5f, -0.5f, 0.5f, 1,0,0,// left  
			  -0.5f, -0.5f, -0.5f, 1,0,0,// right 
			   0.0f,  0.5f, 0.0f,  1,0,1,// top   

			  -0.5f, -0.5f,  0.5f, 1,1,0,// left  
			   0.5f, -0.5f,  0.5f, 1,1,0,// left  
			  -0.5f, -0.5f, -0.5f, 1,1,0,// left  
			   0.5f, -0.5f, -0.5f, 1,1,0,// left  

			  

		};

		uint32_t ind[] = {
			0,1,2,

			3,4,5,

			6,7,8,

			9,10,11,

			12,13,14,

			14,15,13
		};

		Reference<Shader> shader = Shader::Create("D:/DEV/Alpha Studio/Alpha-Studio/asset/shaders/Fragment.glsl", "D:/DEV/Alpha Studio/Alpha-Studio/asset/shaders/Vertex.glsl");
		Reference<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout({ 
			{ ShaderDataType::Float3, "Pos"},
			{ ShaderDataType::Float3, "Col"},

			});
		Reference<IndexBuffer> ibo = IndexBuffer::Create(ind, sizeof(ind));
		Reference<RenderableObject> ref = RenderableObject::Create(vbo, ibo);

		Reference<UniformBuffer> Ubuff = UniformBuffer::Create(sizeof(glm::mat4), 0);

		Ubuff->SetData(&m_EditorCamera.GetViewProjection(), sizeof(glm::mat4));

		shader->Bind();
		Renderer::SetClearColor(0.65f, 0.65f, 0.65f);
		while (m_Window->ShouldClose()) {
			m_Window->NewFrame();


			Renderer::Clear();
			Ubuff->SetData(&m_EditorCamera.GetViewProjection(), sizeof(glm::mat4));
			m_EditorCamera.OnUpdate();
			Renderer::Draw(ref);

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
		Renderer::ResizeWindow(e.GetWidth(), e.GetHeight());
		return false;
	}

}