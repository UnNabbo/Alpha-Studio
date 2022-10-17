#pragma once

#include <string>

namespace Alpha {
	class Asset {
	public:
		std::string& GetPath() { return m_Path; }
		virtual void Reload() {};
	protected:
		void SetPath(std::string path) { m_Path = path; }
	private:
		std::string m_Path = "";
	};
}