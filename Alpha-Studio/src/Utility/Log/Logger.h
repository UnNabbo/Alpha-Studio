#pragma once

#include <iostream>
#include <string>

#include <string_view>

#include <vector>

#include <memory>

namespace std {
	static string to_string(string _Val) {
		return _Val;
	}

	static string to_string(char _Val) {
		return string(1, _Val);
	}

	static string to_string(char * _Val) {
		return string(_Val);
	}

	static string to_string(string_view _Val) {
		return string(_Val);
	}
}


namespace Alpha {

	struct LoggerColor3 {
		int r, g, b;
	};

	enum LoggerLevel {
		Trace = 0,
		Info = 1,
		Warn = 2,
		Error = 3,
		Fatal = 4,
	};

	enum LoggerFlags {
		SHOW_CODE_LINE = 1 << 0,
		SHOW_FILE_NAME = 1 << 1,
		SHOW_CURRENT_TIME = 1 << 2,
		SHOW_LOGGER_NAME = 1 << 3,
		SHOW_COLORED_LOG = 1 << 4,
	};



	class Logger {
	public:

		static std::shared_ptr<Logger> Create(std::string Name, uint32_t m_LogFlags =  SHOW_CURRENT_TIME || SHOW_FILE_NAME || SHOW_LOGGER_NAME);

		void SetColor(LoggerLevel lvl, LoggerColor3 color);
		void SetColor(LoggerLevel lvl, int r, int g, int b);

		template <typename... Args>
		inline void Trace(const char* file, int line, std::string_view text, Args&&... args) {
			std::string txt(format(text, args...));
			FinalizeLog(file, line, txt, LoggerLevel::Trace);
		}

		template <typename... Args>
		inline void Info(const char* file, int line, std::string_view text, Args&&... args) {
			std::string txt(format(text, args...));
			FinalizeLog(file, line, txt, LoggerLevel::Info);
		}

		template <typename... Args>
		inline void Warn(const char* file, int line, std::string_view text, Args&&... args) {
			std::string txt(format(text, args...));
			FinalizeLog(file, line, txt, LoggerLevel::Warn);
		}

		template <typename... Args>
		inline void Error(const char* file, int line, std::string_view text, Args&&... args) {
			std::string txt(format(text, args...));
			FinalizeLog(file, line, txt, LoggerLevel::Error);
		}

		template <typename... Args>
		inline void Fatal(const char* file, int line, std::string_view text, Args&&... args) {
			std::string txt(format(text, args...));
			FinalizeLog(file, line, txt, LoggerLevel::Fatal);
		}

	private:
		Logger(std::string Name, uint32_t m_LogFlag );

		void FinalizeLog(const char* file,int line, std::string& text, LoggerLevel lvl);

		template <typename ...Args>
		static std::string format(std::string_view formatter_text, Args&&... args) {
			std::string str(formatter_text);
			if constexpr (sizeof...(args) != 0) {
				std::string b[] = { std::to_string(args)... };
				int index, I = 0;
				while ((index = str.find("{}")) != std::string::npos) {
					if (I + 1 <= sizeof...(args)) {
						str.replace(index, 2, b[I]);
						I++; 
					}else { str.replace(index, 2, ""); }
				}
			}
			return str;
		}
	private:
		uint32_t m_LogFlags = 0;

		std::string m_Name;
		std::vector<LoggerColor3> m_Colors;
	};

}