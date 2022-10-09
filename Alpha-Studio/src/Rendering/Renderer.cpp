#include "Renderer.h"

#include "Renderer_Internal.h"

#include "API/UniformBuffer.h"

#include "Camera/EditorCamera.h"

#include "glm/glm.hpp"

namespace Alpha {
	struct RedererData {
		Reference<UniformBuffer> CamBuffer;

	};

	inline static RedererData* s_Data = new RedererData();

	void Renderer::Init(){
		Renderer_Internal::Init();

		s_Data->CamBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);
	}

	void Renderer::Begin(EditorCamera& cam){
		glm::mat4 CamMat4 = cam.GetViewProjection();
		s_Data->CamBuffer->SetData(&CamMat4, sizeof(CamMat4), 0);
	}

	void Renderer::Draw(Reference<RenderableObject>& object){
		Renderer_Internal::Draw(object);
	}

	void Renderer::End(){

	}

	void Renderer::Shutdown(){
		Renderer_Internal::Shutdown();
	}

	void Renderer::ResizeWindow(int width, int height){
		Renderer_Internal::ResizeWindow(width, height);
	}

	void Renderer::Clear(){
		Renderer_Internal::Clear();
	}
	void Renderer::SetClearColor(int r, int g, int b){
		Renderer_Internal::SetClearColor(r,g,b);
	}

	API Renderer::GetCurrentAPI()
	{
		return RenderingAPI::GetAPI();
	}
}