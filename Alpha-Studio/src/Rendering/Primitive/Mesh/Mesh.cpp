#include "Mesh.h"

#include "Utility/MeshLoader/MeshLoader.h"

#include "Asset/AssetManager.h"

#include "Rendering/Primitive/RenderableObject.h"



namespace Alpha {

	Mesh3D::Mesh3D(std::string_view path) : m_Meshes(MeshLoader::Load(path)) {
		SetPath(path);
		CreateRenderableObject();
	}

	Mesh3D::Mesh3D(std::vector<MeshData>& meshes) : m_Meshes(meshes){
		CreateRenderableObject();
	}

	Mesh3D::~Mesh3D()
	{

	}

	void Mesh3D::Reload() {
		m_Meshes = MeshLoader::Load(GetPath());
	}

	Reference<Mesh3D> Mesh3D::Create(std::string_view path) { 
		auto mesh = AssetManager::Retrive<Mesh3D>(path);
		if (!mesh.get()) {
			mesh = AssetManager::CreateAsset<Mesh3D>(path);
		}
		return mesh;
	}

	void Mesh3D::CreateRenderableObject() {
		Reference<VertexBuffer> vbo = VertexBuffer::Create(m_Meshes[0].Vertices.data(), m_Meshes[0].Vertices.size() * sizeof(struct Vertex));
		vbo->SetLayout({
				{ ShaderDataType::Float3, "Pos"},
				{ ShaderDataType::Float3, "Normals"},
				{ ShaderDataType::Float2, "Uvs"},
				{ ShaderDataType::Float3, "Normals"},
				{ ShaderDataType::Float3, "Normals"},

				});
		Reference<IndexBuffer> ibo = IndexBuffer::Create(m_Meshes[0].Indicies.data(), m_Meshes[0].Indicies.size() * sizeof(uint32_t));
		
		m_RendObj = RenderableObject::Create(vbo, ibo);

	}

}