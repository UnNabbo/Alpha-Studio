#include "RendererCommand.h"

namespace Alpha {
	void RendererCommand::Init(){
		s_RenderingAPI->Init();

	}
	void RendererCommand::ResizeWindow(int width, int height){
		s_RenderingAPI->ResizeWindow(width, height);
	}
	void RendererCommand::Clear(){
		s_RenderingAPI->Clear();
	}
	void RendererCommand::SetClearColor(int r, int g, int b){
		s_RenderingAPI->SetClearColor(r, g, b);

	}
	void RendererCommand::Shutdown(){
		s_RenderingAPI->Shutdown();

	}

	API RendererCommand::GetCurrentAPI()
	{
		return RenderingAPI::GetAPI();
	}

}