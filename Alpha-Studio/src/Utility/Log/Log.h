#pragma once

#include "Logger.h"

#include <memory>

namespace Alpha 
{
	class Log {
	public:

		static void Init();

		inline static std::shared_ptr<Logger> getCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<Logger> getClientLogger() { return s_ClientLogger; };


	private:

		inline static std::shared_ptr<Logger> s_CoreLogger;
		inline static std::shared_ptr<Logger> s_ClientLogger;
	};
}

#ifdef ALPHA_CORE

#define ALPHA_TRACE(...) ::Alpha::Log::getCoreLogger()->Trace(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_INFO(...) ::Alpha::Log::getCoreLogger()->Info(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_WARN(...) ::Alpha::Log::getCoreLogger()->Warn(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_ERROR(...) ::Alpha::Log::getCoreLogger()->Error(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_FATAL(...) ::Alpha::Log::getCoreLogger()->Fatal(__FILE__, __LINE__, __VA_ARGS__)

#define ALPHA_ASSERT(x, ...) if(!x) { ::Origin::Log::getCoreLogger()->Fatal(__FILE__, __LINE__, __VA_ARGS__); __debugbreak(); }

#else


#define ALPHA_TRACE(...) ::Alpha::Log::getClientLogger()->Trace(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_INFO(...) ::Alpha::Log::getClientLogger()->Info(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_WARN(...) ::Alpha::Log::getClientLogger()->Warn(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_ERROR(...) ::Alpha::Log::getClientLogger()->Error(__FILE__, __LINE__, __VA_ARGS__)
#define ALPHA_FATAL(...) ::Alpha::Log::getClientLogger()->Fatal(__FILE__, __LINE__, __VA_ARGS__)

#define ALPHA_ASSERT(x, ...) if(!x) { ::Alpha::Log::getCoreLogger()->Fatal(__FILE__, __LINE__, __VA_ARGS__); __debugbreak(); }

#endif 