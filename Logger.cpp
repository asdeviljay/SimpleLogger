#include "pch.h"
#include "Logger.hpp"
#include "CWStd.hpp"
#include <iostream>

const std::string Logger::m_fileName = "error.log";
Logger* Logger::m_pInstance = nullptr;
std::ofstream Logger::m_logFile;
const std::string Logger::m_tagName[3] = { "INFO", "WARRING", "ERROR" };

Logger::Logger()
{
}


Logger::~Logger()
{
	m_logFile.close();
}

Logger* Logger::instance() {
	if (m_pInstance == nullptr) {
		m_pInstance = new Logger();
		m_logFile.open(m_fileName, std::ios::out | std::ios::app);
		PROMISED(m_logFile);
		PROMISED(m_logFile.is_open());
	}
	PROMISED(m_pInstance != nullptr);
	return m_pInstance;
}

void Logger::Log(const unsigned int t_tag, const std::string& t_message) {
	REQUIRED(t_tag == 0 || t_tag == 1 || t_tag == 2);
	switch (t_tag)
	{
	case 0:
	case 1:
		std::cout << t_message << std::endl;
		m_logFile << "[" << m_tagName[t_tag] << "] ";
		m_logFile << t_message << std::endl;
		break;
	case 2:
		std::cout << "Function: " << __FUNCTION__ << "\n" << 
			"Directory: " << __FILE__ << "\n" <<
			"Line: " << __LINE__ << std::endl;
		std::cout << t_message << std::endl;
		m_logFile << "[" << m_tagName[t_tag] << "] ";
		m_logFile << "Function: " << __FUNCTION__ << "\n" <<
			"Directory: " << __FILE__ << "\n" <<
			"Line: " << __LINE__ << std::endl;
		m_logFile << t_message << std::endl;
		break;
	default:
		break;
	}
}

void Logger::releaseInstance() {
	REQUIRED(m_pInstance != nullptr);
	delete(m_pInstance);
}

/*void Logger::Log(const unsigned int t_tag, const char* t_message) {
	std::string cvt2Str(t_message);
	Logger::Log(t_tag, cvt2Str);
}*/
