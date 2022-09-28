#include "Logger.h"

#include <unordered_map>
#include <sstream>
#include <chrono>
#include <ctime>    

namespace Alpha {

	struct LoggerData {
		
	};

	Logger::Logger(std::string Name, uint32_t LogFlags) : m_Name(Name), m_LogFlags(LogFlags)
	{
		m_Colors.push_back({ 255,255,255 });
		m_Colors.push_back({ 0,255,0 });
		m_Colors.push_back({ 255,255,00 });
		m_Colors.push_back({ 255,0,0 });
		m_Colors.push_back({ 139,0,0 });

	}

	void Logger::FinalizeLog(const char* file, int line, std::string& text, LoggerLevel lvl)
	{

		std::stringstream ss;

		if (m_LogFlags & SHOW_COLORED_LOG) {
			auto& color = m_Colors[lvl];
			ss << format("\033[38;2;{};{};{}m", color.r, color.g, color.b);
		}

		if (m_LogFlags & SHOW_CURRENT_TIME) {
			time_t now = time(0);
			struct tm  tstruct;
			char       buf[80];
			tstruct = *localtime(&now);
			strftime(buf, sizeof(buf), "%X", &tstruct);
			ss << "[" << buf << "]";
		}

		if (m_LogFlags & SHOW_FILE_NAME) {
			std::string str_file = file;
			str_file = (str_file.find('\\')) ? str_file = str_file.substr(str_file.find_last_of('\\') + 1, str_file.length()) : str_file = str_file.substr(str_file.find_last_of('/') + 1, str_file.length());
			ss << "[File: " << str_file << "]";
		}

		if (m_LogFlags & SHOW_CODE_LINE) { ss << "[Line: " << line << "]"; }
		if (m_LogFlags & SHOW_LOGGER_NAME) { ss << " " << m_Name << ":"; }
		if (m_LogFlags) { ss << " "; }

		ss << text;

		if (m_LogFlags & SHOW_COLORED_LOG) { ss << " \033[38;5;255m"; }

		ss << std::endl;

		//TODO ADD SUPPORT FOR OTHER OUTPUT SYSTEMS
		std::cout << ss.str();
		//END TODO
	}

	std::shared_ptr<Logger> Logger::Create(std::string Name, uint32_t LogFlags)
	{
		return std::shared_ptr<Logger>(new Logger(Name, LogFlags));
	}

	void Logger::SetColor(LoggerLevel lvl,LoggerColor3 color)
	{
		m_Colors[lvl] = color;
	}

	void Logger::SetColor(LoggerLevel lvl, int r, int g, int b)
	{
		m_Colors[lvl] = LoggerColor3{r,g,b};
	}
}