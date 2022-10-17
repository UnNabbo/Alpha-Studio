#pragma once

#include <iostream>
#include "Rendering/Primitive/Mesh/Vertex.h"

namespace Alpha {
	struct ModelData {
		std::vector<struct Vertex> Vertices;
		std::vector<uint32_t> Indicies;
	};

	class ModelLoader {
	public:
		static ModelData Load(std::string_view path);
	};
}