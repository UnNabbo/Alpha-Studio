#include "FileWatcher.h"

#include "Core/Core.h"

#include <string>

#include "AssetManager.h"

namespace Alpha {
	void FileWatcher::Insert(std::string path) {
		m_Paths[path] = std::filesystem::last_write_time(path);
	}

	void FileWatcher::Check() {
		for (auto& [file, last_write_time ]: m_Paths) {
			auto current_file_last_write_time = std::filesystem::last_write_time(file);
			if (last_write_time != current_file_last_write_time) {
				last_write_time = current_file_last_write_time;
				auto res = AssetManager::Retrive<Asset>(file);
				res->Reload();
				ALPHA_INFO("{}", file);
			}
		}
	}
}