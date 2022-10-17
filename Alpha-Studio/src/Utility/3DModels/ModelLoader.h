#pragma once

#include "Core/Core.h"

#include <iostream>
#include <vector>

#include "Rendering/Primitive/Mesh/Vertex.h"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace Alpha {

	struct ModelData {
		std::vector<struct Vertex> Vertices;
		std::vector<uint32_t> Indicies;
	};

	class ModelLoader {
	public:
		static ModelData Load(std::string_view path);
	private:
		static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<aiMesh*> &mesh);
	};
}