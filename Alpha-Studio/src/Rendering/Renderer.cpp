#include "Renderer.h"

#include "RendererCommand.h"

#include "Primitive/UniformBuffer.h"

#include "Camera/EditorCamera.h"
#include "RenderingQueue.h"
#include "RenderCommandFn.h"

#include "glm/glm.hpp"

#include "Primitive/Mesh/Mesh.h"

namespace Alpha {

	struct RedererData {
		Reference<UniformBuffer> CamBuffer;
		RenderingQueue Queue;
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

	void Renderer::Render(){
		s_Data->Queue.Execute();
	}

	void Renderer::Submit(Reference<Mesh3D>& object) {
		auto data = object->GetRenderableObject();
		auto command = RenderingCommand::Create(RendererCommand::Draw, data);

		ObjectKey key;
		s_Data->Queue.SubmitObject(command, key);
	}

	void Renderer::End(){

	}

	void Renderer::Shutdown(){
		RendererCommand::Shutdown();
	}


}