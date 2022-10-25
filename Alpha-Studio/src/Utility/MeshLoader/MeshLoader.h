#pragma once

#include "Core/Core.h"

#include <iostream>
#include <vector>

#include "Rendering/Primitive/Mesh/Vertex.h"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace Alpha {

	class MeshLoader {
	public:
		static std::vector<MeshData> Load(std::string_view path, bool overwrite = false);
	private:
		static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<aiMesh*> &mesh);
	};
}