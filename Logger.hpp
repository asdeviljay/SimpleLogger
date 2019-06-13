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

	static const unsigned int INFO = 0;
	static const unsigned int WARRING = 1;
	static const unsigned int ERROR = 2;

private:
	Logger();
	Logger(const Logger&) {};
	Logger& operator=(const Logger&) { return *this; };

	static Logger* m_pInstance;
	static const std::string m_fileName;
	static std::ofstream m_logFile;
	static const std::string m_tagName[];
};

