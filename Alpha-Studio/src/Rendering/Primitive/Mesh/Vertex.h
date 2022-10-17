#pragma once

#include "glm/glm.hpp"

#define MAX_BONE_INFLUENCE 4

namespace Alpha {
	struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UVs;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
	};
}