#pragma once

#include "../BinaryData.h"

namespace Alpha {
	template<class Archive, class T, class A>
	void Serialize(Archive& archive, std::vector<T, A>& vec) {
		auto data = DATA(0, 0, vec.size());
		archive& data;
		int i = 0;
		for (auto& item : vec) {
			archive& Serializer::CreateNVP("Index" + std::to_string(i++), item);
		}
	}

	template<class Archive, class T, class A>
	void Deserialize(Archive& archive, std::vector<T, A>& vec) {
		auto data = DATA(0, 0, vec.size());
		archive& data;
		vec.resize(data.Size_Tag);
		int i = 0;
		for (auto& item : vec) {
			archive & Serializer::CreateNVP("Index" + std::to_string(i++), item);
		}
	}
}