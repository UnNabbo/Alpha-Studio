#pragma once

#include "Core/Core.h"

#include "Asset/Asset.h"

#include "glm/glm.hpp"

#include "Vertex.h"

namespace Alpha {
	class RenderableObject;

	class Mesh3D : public Asset {
	public:
		Mesh3D(std::string_view path);
		Mesh3D(std::vector<MeshData>& meshes);
		~Mesh3D();
		
		inline MeshData& GetData(int index) { return m_Meshes[index]; }
		inline std::vector<MeshData> GetData() { return m_Meshes; }

		virtual void Reload() override;

		static Reference<Mesh3D> Create(std::string_view path);
		inline Reference<RenderableObject>& GetRenderableObject() { return m_RendObj; };

		template<class Archive>
		void Serialize(Archive& archive) {
			archive& MEMBER(m_Meshes);
		}

	private:
		void CreateRenderableObject();
	private:
		std::vector<MeshData> m_Meshes;
		Reference<RenderableObject> m_RendObj;
	};
}