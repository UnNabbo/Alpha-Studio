#pragma once

#include "RendererCommand.h"

#include "Renderer_Internal.h"

namespace Alpha {
	void RendererCommand::Init(){
		Renderer_Internal::Init();
	}
	void RendererCommand::ResizeWindow(int width, int height){
		Renderer_Internal::ResizeWindow(width, height);
	}
	void RendererCommand::Clear(){
		Renderer_Internal::Clear();
	}
	void RendererCommand::SetClearColor(int r, int g, int b){
		Renderer_Internal::SetClearColor(r, g, b);
	}
	void RendererCommand::Shutdown(){
		Renderer_Internal::Shutdown();
	}

	API RendererCommand::GetCurrentAPI()
	{
		return RenderingAPI::GetAPI();
	}

}