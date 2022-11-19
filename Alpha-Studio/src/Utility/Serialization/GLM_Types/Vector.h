#pragma once

#include "glm/glm.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <array>
#include <memory>
#include <string>

#include "Utility/Serialization/Serializer.h"

namespace Alpha {
	inline static std::string Comp[4] = { "X", "Y", "Z", "W"};

	template<class Archive,typename T, glm::qualifier Q>
	void Serialize(Archive& archive, glm::vec<1, T, Q> vec ) {
		std::array<float, 1> arr;
		memcpy(arr.data(), glm::value_ptr(vec), sizeof(T) * 1);

		uint32_t i = 0;
		for (auto& item : arr) {
			archive& Serializer::CreateNVP(Comp[i++], item);
		}
	}
	template<class Archive, typename T, glm::qualifier Q>
	void Serialize(Archive& archive, glm::vec<2, T, Q> vec) {
		std::array<float, 2> arr;
		memcpy(arr.data(), glm::value_ptr(vec), sizeof(T) * 2);

		uint32_t i = 0;
		for (auto& item : arr) {
			archive& Serializer::CreateNVP(Comp[i++], item);
		}

	}

	template<class Archive, typename T, glm::qualifier Q>
	void Serialize(Archive& archive, glm::vec<3, T, Q> vec) {
		std::array<float, 3> arr;
		memcpy(arr.data(), glm::value_ptr(vec), sizeof(T) * 3);

		uint32_t i = 0;
		for (auto& item : arr) {
			archive& Serializer::CreateNVP(Comp[i++], item);
		}
	}

	template<class Archive, typename T, glm::qualifier Q>
	void Serialize(Archive& archive, glm::vec<4, T, Q> vec) {
		std::array<float, 4> arr;
		memcpy(arr.data(), glm::value_ptr(vec), sizeof(T) * 4);

		uint32_t i = 0;
		for (auto& item : arr) {
			archive& Serializer::CreateNVP(Comp[i++], item);
		}

	}
}