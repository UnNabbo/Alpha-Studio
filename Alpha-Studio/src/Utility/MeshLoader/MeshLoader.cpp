#include "MeshLoader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <fstream>

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha {
	namespace Utils {
		glm::vec3 ToVec3(aiVector3D* vec) {
			return { vec->x, vec->y, vec->z};
		}

		std::string GetChachePath() {
			return "./asset/models/chache/";
		}
	}

	std::vector<MeshData> MeshLoader::Load(std::string_view path, bool overwrite) {
		std::vector<MeshData> PMeshes;

		std::string strpath(path);

		std::string name = strpath.substr(strpath.find_last_of("/"), strpath.find_last_of("."));

		
		std::fstream file(Utils::GetChachePath() + name + ".model", std::ios::in | std::ios::binary);

		if (file.is_open()) {
			std::vector<char> buffer;

			{
				file.seekg(0, std::ios::end);
				auto size = file.tellg();
				file.seekg(0, std::ios::beg);

				buffer.resize(size);
				file.read((char*)buffer.data(), size);
			}

			size_t offset = 0;

			size_t size = *(size_t*)buffer.data();
			offset += sizeof(size_t);

			PMeshes.resize(size);

			for (auto& mesh : PMeshes) {
				size_t data_size = *(size_t*)(buffer.data() + offset);
				offset += sizeof(size_t);

				mesh.Vertices.resize(data_size / sizeof(Vertex));
				memcpy(mesh.Vertices.data(), buffer.data() + offset, data_size);
				offset += data_size;

				size_t index_size = *(size_t*)(buffer.data() + offset);
				offset += sizeof(size_t);

				mesh.Indicies.resize(index_size / sizeof(uint32_t));
				memcpy(mesh.Indicies.data(), buffer.data() + offset, index_size);
				offset += index_size;
			}

			return PMeshes;
		} else {

			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(std::string(path), aiProcess_PreTransformVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
			if (!scene) {
				ALPHA_FATAL("Could not load {}", path);
				return {};
			}

			std::vector<aiMesh*> meshes;

			ProcessNode(scene->mRootNode, scene, meshes);


			for (int i = 0; i < meshes.size(); i++) {
				auto& Mesh = meshes[i];

				std::vector<uint32_t> indices;
				std::vector<Vertex> vertices;

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

				PMeshes.push_back({ vertices, indices });
			}

			std::fstream file(Utils::GetChachePath() + name + ".model", std::ios::out | std::ios::binary | std::ios::app);

			size_t size = PMeshes.size();
			file.write((char*)&size, sizeof(size_t));

			for (auto& mesh : PMeshes) {
				size = mesh.Vertices.size() * sizeof(Vertex);
				file.write((char*)&size, sizeof(size_t));
				file.write((char *)mesh.Vertices.data(), mesh.Vertices.size() * sizeof(Vertex));
				size = mesh.Indicies.size() * sizeof(uint32_t);
				file.write((char*)&size, sizeof(size_t));
				file.write((char *)mesh.Indicies.data(), mesh.Indicies.size() * sizeof(uint32_t));
			}
		}

		return PMeshes;

	}
	void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<aiMesh*>& meshes)
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

