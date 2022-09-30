#pragma once

#include <memory>

#include "Utility/Log/Log.h"


template<typename type>
using Reference = std::shared_ptr<type>;

template<typename type>
using ScopedRef = std::unique_ptr<type>;

template<typename type, typename ... Args>
constexpr Reference<type>MakeReference(Args&& ... args) {
	return std::make_shared<type>(std::forward<Args>(args)...);
}

template<typename type, typename ... Args>
constexpr Reference<type>MakeScopedRef(Args&& ... args) {
	return std::make_unique<type>(std::forward<Args>(args)...);
}