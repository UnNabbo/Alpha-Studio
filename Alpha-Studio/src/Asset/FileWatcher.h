#pragma once

#include <filesystem>
#include <unordered_map>

#include <functional>
namespace Alpha {
    class FileWatcher {
    public:
        void Insert(std::string path);
        void Check();
    private:
        std::unordered_map<std::string, std::filesystem::file_time_type> m_Paths;


    };
}