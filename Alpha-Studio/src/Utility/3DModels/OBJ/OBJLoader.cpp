#include "OBJLoader.h"

#include <fstream>

#include <string>

#include "Rendering/Primitive/Mesh/Vertex.h"

namespace Alpha {
	namespace Utils {
		glm::vec3 ToVec3(std::string str) {
			double vec[3]; 
			size_t c_index = 0;
			for (int i = 0; i < 3; i++) {
				size_t index = str.find(" ", c_index);
				if (index != std::string::npos) {
					vec[i] = std::stod(str.substr(c_index, index));
					c_index = index + 1;
				}
				else {
					vec[i] = std::stod(str.substr(c_index, str.length()));

				}

			}
			return { vec[0], vec[1], vec[2] };
		}

		glm::vec3 ToVec3I(std::string str) {
			int vec[3];
			size_t c_index = 0;
			for (int i = 0; i < 3; i++) {
				size_t index = str.find(" ", c_index);
				if (index != std::string::npos) {
					vec[i] = std::stoi(str.substr(c_index, index));
					c_index = index + 1;
				}
				else {
					vec[i] = std::stoi(str.substr(c_index, str.length()));

				}

			}
			return { vec[0], vec[1], vec[2] };
		}

		glm::vec2 ToVec2(std::string str) {
			double vec[3];
			size_t c_index = 0;
			for (int i = 0; i < 2; i++) {
				size_t index = str.find(" ", c_index);
				if (index != std::string::npos) {
					vec[i] = std::stod(str.substr(c_index, index));
					c_index = index + 1;
				}
				else {
					vec[i] = std::stod(str.substr(c_index, str.length()));

				}

			}
			return { vec[0], vec[1]};
		}
	}

	OBJFile::OBJFile(std::string_view path) : m_Path(path) {
		LoadFile();
	}

	OBJFile::~OBJFile(){

	}

	void OBJFile::LoadFile() {
		std::ifstream file(m_Path);

		if (file.is_open()) {
			std::string buff;

			std::vector<glm::vec3> vertex;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec3> indices;

			while (std::getline(file, buff)) {
				if (buff[0] == 'v') {
					switch (buff[1])
					{
					case ' ':
						vertex.push_back(Utils::ToVec3(buff.substr(2, buff.length())));
						break;
					case 'n':
						normals.push_back(Utils::ToVec3(buff.substr(3, buff.length())));
						break;
					case 't':
						uvs.push_back(Utils::ToVec2(buff.substr(3, buff.length())));
						break;
					default:
						break;
					}
				}
				if (buff[0] == 'f') {
					std::string s = buff.substr(2, buff.length());
					for (auto& c : s) {
						if (c == ' ') c = '#';
						if (c == '/') c = ' ';
					}

					bool end = false;
					size_t c_index = 0;
					while (!end) {
						size_t index = s.find("#", c_index);
						if (index != std::string::npos) {
							indices.push_back(Utils::ToVec3I(s.substr(c_index, index)));
							c_index = index + 1;
						}
						else {
							indices.push_back(Utils::ToVec3I(s.substr(c_index, s.length())));
							end = true;
						}
					}
				}
			}
			for (auto& index : indices) {
				m_Vertices.push_back({ vertex[index.x - 1], normals[index.z - 1], uvs[index.y - 1] });
			}
		}
	}
}