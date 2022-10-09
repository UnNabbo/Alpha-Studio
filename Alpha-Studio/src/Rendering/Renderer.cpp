#include "Renderer.h"

#include "RendererCommand.h"

#include "Primitive/UniformBuffer.h"

#include "Camera/EditorCamera.h"

#include "Renderer_Internal.h"

#include "glm/glm.hpp"

namespace Alpha {
	struct RedererData {
		Reference<UniformBuffer> CamBuffer;
	};

	inline static RedererData* s_Data = new RedererData();

	void Renderer::Init(){
		RendererCommand::Init();
		s_Data->CamBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);
	}

	void Renderer::Begin(EditorCamera& cam){
		glm::mat4 CamMat4 = cam.GetViewProjection();
		s_Data->CamBuffer->SetData(&CamMat4, sizeof(CamMat4), 0);
	}

	void Renderer::Draw(Reference<RenderableObject>& object){
		Renderer_Internal::Draw(object);
	}

	void Renderer::Submit(Reference<RenderableObject>& object) {
		
	}

	void Renderer::End(){

	}

	void Renderer::Shutdown(){
		RendererCommand::Shutdown();
	}


}