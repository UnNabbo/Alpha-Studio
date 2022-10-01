#include "Renderer.h"

#include "Renderer_Internal.h"

namespace Alpha {
	void Renderer::Init(){
		Renderer_Internal::Init();
	}

	void Renderer::Shutdown(){
		Renderer_Internal::Shutdown();
	}

	void Renderer::ResizeWindow(){
		Renderer_Internal::ResizeWindow();
	}

	void Renderer::Draw(Reference<RenderableObject>& object){
		Renderer_Internal::Draw(object);
	}


	void Renderer::Clear(){
		Renderer_Internal::Clear();
	}
	void Renderer::Clear(int r, int g, int b){
		Renderer_Internal::Clear();
	}

	API Renderer::GetCurrentAPI()
	{
		return RenderingAPI::GetAPI();
	}
}