#pragma once

#include <array>
#include <string>

#include "Utility/Serialization/Serializer.h"

namespace Alpha {
	template<class Archive, class T, size_t Size>
	void Serialize(Archive& archive, std::array<T, Size>& const array) {
		auto data = DATA(0, 0, 0);
		archive& data;
		int i = 0;
		for (auto& item : array){
			archive& Serializer::CreateNVP("Index" + std::to_string(i++), item);
		}
	}
}