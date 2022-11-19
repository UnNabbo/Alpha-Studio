#pragma once

#include <vector>

namespace Alpha {
	namespace Serializer {
		struct BinaryData {
			size_t Identifer_Size = 0;
			std::vector<char> Identifer{};

			size_t Size_Tag = 0;

			size_t Data_Size = 0;
			std::vector<char> Data{};
		};

	}
}