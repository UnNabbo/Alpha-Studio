#include "ModelLoader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha {
	namespace Utils {
		glm::vec3 ToVec3(aiVector3D* vec) {
			return { vec->x, vec->y, vec->z};
		}
	}

	ModelData ModelLoader::Load(std::string_view path) {
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(std::string(path), aiProcess_PreTransformVertices  | aiProcess_Triangulate  | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace );
		if (!scene) {
			ALPHA_FATAL("Could not load {}", path);
			return {};
		}

		std::vector<uint32_t> indices;
		std::vector<Vertex> vertices;

		std::vector<aiMesh*> meshes;

		ProcessNode(scene->mRootNode, scene, meshes);

		for (auto & Mesh : meshes) {

			for (uint32_t i = 0; i < Mesh->mNumVertices; i++) {
				Vertex current_vertex;
				current_vertex.Position = Utils::ToVec3(&Mesh->mVertices[i]);
				current_vertex.Normal = (Mesh->HasNormals()) ? Utils::ToVec3(&Mesh->mNormals[i]) : glm::vec3(0, 0, 0);
				if (Mesh->mTextureCoords[0]) {
					current_vertex.UVs = Utils::ToVec3(&Mesh->mTextureCoords[0][i]);
					current_vertex.Tangent = Utils::ToVec3(&Mesh->mTangents[i]);
					current_vertex.Bitangent = Utils::ToVec3(&Mesh->mBitangents[i]);
				}
				else {
					current_vertex.UVs = { 0,0 };
					current_vertex.Tangent = { 0, 0, 0 };
					current_vertex.Bitangent = { 0, 0, 0 };
				}

				vertices.push_back(current_vertex);
			}

			for (uint32_t i = 0; i < Mesh->mNumFaces; i++) {
				const auto& face = Mesh->mFaces[i];
				if (face.mNumIndices == 3) {
					indices.push_back(face.mIndices[0]);
					indices.push_back(face.mIndices[1]);
					indices.push_back(face.mIndices[2]);
				}
			}
		}

		return {vertices, indices};

	}
	void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<aiMesh*>& meshes)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(mesh);
		}
		for (uint32_t i = 0; i < node->mNumChildren; i++) {
			ProcessNode(node->mChildren[i], scene, meshes);
		}
	}
}

