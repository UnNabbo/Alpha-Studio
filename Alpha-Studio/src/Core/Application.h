#pragma once

namespace Alpha 
{
	class Application {
	public:

		Application();

		virtual void OnStart();
		virtual void OnUpdate();
		void Run();

		virtual ~Application();

	private:	
		

		
	};

}

