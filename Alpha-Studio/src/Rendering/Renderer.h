#pragma once

#include "Core/Core.h"

#include "RenderingAPI.h"

namespace Alpha {
	class Mesh3D;
	class Renderer {
	public:
		static void Init();

		static void Shutdown();

		static void Begin(EditorCamera& cam);

		static void Render();
		static void Submit(Reference<Mesh3D>& object);

		static void End();
	private:


	};
}