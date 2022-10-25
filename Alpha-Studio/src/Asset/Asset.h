#pragma once

#include <string>

namespace Alpha {
	class Asset {
	public:
		std::string& GetPath() { return m_path; }
		virtual void Reload() {};
	protected:
		void SetPath(std::string path) { m_path = path; }
		void SetPath(std::string_view path) { m_path = std::string(path); }
	private:
		std::string m_path = "";
	};
}