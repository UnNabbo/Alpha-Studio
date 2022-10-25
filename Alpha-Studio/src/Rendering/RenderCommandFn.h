#pragma once

#include "Core/Core.h"

namespace Alpha {

	template <typename Type, typename... Args>
	class RenderingCommandFn;

	class RenderingCommand {
	public:
		template <typename Type, typename... Args>
		static Reference<RenderingCommand> Create(Type fn, Args... args) { return MakeReference<RenderingCommandFn<Type, Args...>>(fn, args...); }

		virtual void Execute() {};
	};

	template <typename Type, typename... Args>
	class RenderingCommandFn : public RenderingCommand {
	public:
		RenderingCommandFn(Type fn, Args... args) : m_FnPtr(fn), m_Args(args...) {}
		virtual void Execute() override { std::apply(m_FnPtr, m_Args); };
	private:
		Type m_FnPtr;
		std::tuple<Args...> m_Args;
	};

}