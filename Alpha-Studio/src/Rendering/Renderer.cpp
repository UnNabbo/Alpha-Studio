#include "Renderer.h"

#include "Renderer_Internal.h"

namespace Alpha {
	void Renderer::Init(){
		Renderer_Internal::Init();
	}

	void Renderer::Shutdown(){
		Renderer_Internal::Shutdown();
	}

	void Renderer::ResizeWindow(int width, int height){
		Renderer_Internal::ResizeWindow(width, height);
	}

	void Renderer::Begin(EditorCamera& cam){
		Renderer_Internal::Begin(cam);
	}

	void Renderer::Draw(Reference<RenderableObject>& object){
		Renderer_Internal::Draw(object);
	}

	void Renderer::End(){

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