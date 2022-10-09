#pragma once

#include "Core/Core.h"

#include "RenderingAPI.h"

namespace Alpha {
	class Renderer {
	public:
		static void Init();

		static void Shutdown();

		static void Begin(EditorCamera& cam);

		static void Draw(Reference<RenderableObject>& object);
		static void Submit(Reference<RenderableObject>& object);

		static void End();
	private:


	};
}