#include "Application.h"

#include "Core/Window/Window.h"

#include "Rendering/API/RenderableObject.h"

#include "Rendering/Renderer.h"

#include "Rendering/API/Shader.h"

#include "glad/glad.h"

namespace Alpha 
{
	inline Application* s_App = 0;

	Application::Application() {
		if (s_App) {};
		s_App = this;
		Log::Init();

		m_Window = Window::Create();

		Renderer::Init();
	}

	void Application::OnStart(){
		
	}

	void Application::OnUpdate(){

	}

	void Application::Run(){
		OnStart();

		float vertices[] = {
			  -0.5f, -0.5f, 0.0f, // left  
			   0.5f, -0.5f, 0.0f, // right 
			   0.0f,  0.5f, 0.0f  // top   
		};

		uint32_t ind[] = {
			0,1,2,
		};

		Reference<Shader> shader = Shader::Create("D:/DEV/Alpha Studio/Alpha-Studio/asset/shaders/Fragment.glsl", "D:/DEV/Alpha Studio/Alpha-Studio/asset/shaders/Vertex.glsl");
		Reference<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout({ { ShaderDataType::Float3, "Pos"} });
		Reference<IndexBuffer> ibo = IndexBuffer::Create(ind, sizeof(ind));
		Reference<RenderableObject> ref = RenderableObject::Create(vbo, ibo);

		shader->Bind();
		glClearColor(0, 1, 0, 1.0f);
		while (m_Window->ShouldClose()) {
			m_Window->NewFrame();

			Renderer::Clear();

			Renderer::Draw(ref);

			OnUpdate();
		}
	}

	Application::~Application() {

	}

}