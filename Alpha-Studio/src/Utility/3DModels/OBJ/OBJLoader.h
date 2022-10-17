#pragma once

#include "Core/Core.h"

#include <iostream>

#include "Rendering/Primitive/Mesh/Vertex.h"


namespace Alpha {
	class OBJFile {
	public:
		OBJFile(std::string_view path);
		~OBJFile();

		void* GetData() { return m_Vertices.data(); }
		size_t GetSize() { return m_Vertices.size(); }

	private:

		void LoadFile();
	private:
		std::string m_Path;
		std::vector<uint32_t> m_Indices;
		std::vector<struct Vertex> m_Vertices;
	};
}