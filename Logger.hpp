#pragma once

#include <fstream>
//#include <iostream>
//#include <cstdarg>
#include <string>

//#define INFO 0

class Logger
{
public:
	~Logger();
	static Logger* instance();
	void Log(const unsigned int t_tag, const std::string& t_message);
	static void releaseInstance();

	const enum logLevel {
		INFO, WARNING, ERROR
	};

private:
	Logger();
	Logger(const Logger&) {};
	Logger& operator=(const Logger&) { return *this; };

	static Logger* m_pInstance;
	static const std::string m_fileName;
	static std::ofstream m_logFile;
	static const std::string m_tagName[];
};

