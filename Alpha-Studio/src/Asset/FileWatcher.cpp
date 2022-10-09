#include "FileWatcher.h"

#include "Core/Core.h"

#include <string>

#include "AssetManager.h"

namespace Alpha {
	void FileWatcher::Insert(std::string path) {
		m_Paths[path] = std::filesystem::last_write_time(path);
	}

	void FileWatcher::Check() {
		for (auto& file : std::filesystem::recursive_directory_iterator("./")) {
			auto path = file.path().string();
			size_t pos = path.find("\\");

			while (pos != std::string::npos)
			{
				path.replace(pos, 1, 1, '/');
				pos = path.find("\\");
			}

			if (m_Paths.find(path) != m_Paths.end()) {
				auto current_file_last_write_time = std::filesystem::last_write_time(file);
				if (m_Paths[path] != current_file_last_write_time) {
					m_Paths[path] = current_file_last_write_time;
					auto res = ResourceManager::Retrive<Resource>(path);
					res->Reload();
					ALPHA_INFO("{}", file.path().string());
				}
			}
		}
	}
}