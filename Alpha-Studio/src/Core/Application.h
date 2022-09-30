#pragma once

#include "Core/Core.h"

namespace Alpha 
{
	class Window;
	class Application {
	public:

		Application();

		virtual void OnStart();
		virtual void OnUpdate();
		void Run();

		virtual ~Application();

	private:	
		Reference<Window> m_Window;

		
	};

}

