#include "Log.h"

namespace Alpha 
{
	void Log::Init()
	{
		s_CoreLogger = Logger::Create("Alpha Studio", SHOW_CURRENT_TIME | SHOW_LOGGER_NAME | SHOW_COLORED_LOG);
		s_ClientLogger = Logger::Create("App", SHOW_CURRENT_TIME | SHOW_LOGGER_NAME | SHOW_COLORED_LOG);

	}

}