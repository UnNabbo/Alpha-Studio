#pragma once

#include "glm/glm.hpp"

#include "Utility/Serialization/Serializer.h"

#define MAX_BONE_INFLUENCE 4

namespace Alpha {
	struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UVs;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;

		template<class Archive>
		void Serialize(Archive& archive) {
			archive& MEMBER(Position);
			archive& MEMBER(Normal);
			archive& MEMBER(UVs);
			archive& MEMBER(Tangent);
			archive& MEMBER(Bitangent);
		}
	};

    struct MeshData {
        std::vector<struct Vertex> Vertices;

        std::vector<uint32_t> Indicies;

		template<class Archive>
		void Serialize(Archive& archive) {
			archive& MEMBER(Vertices);
			archive& MEMBER(Indicies);
		}
    };
}