#pragma once

#include "../BinaryData.h"

namespace Alpha {
	template<class Archive, class CharT, class Traits, class Alloc>
	void Serialize(Archive& archive, std::basic_string<CharT, Traits, Alloc>& str) {
		auto data = DATA(str.data(), str.size(), str.size());
		archive& data;
	}

	template<class Archive, class CharT, class Traits, class Alloc>
	void Deserialize(Archive& archive, std::basic_string<CharT, Traits, Alloc>& str) {
		auto data = DATA(str.data(), str.size(), str.size());

		archive& data;

		str.resize(data.Size_Tag);
		memcpy(str.data(), data.Data.data(), data.Data_Size);
	}
}