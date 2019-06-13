#include "pch.h"
#include "CWUTest.hpp"
#include "CWStd.hpp"
#include "Logger.hpp"
#include <iostream>

CWUTest::CWUTest() :
	m_passTest(0),
	m_failTest(0)
{
}


CWUTest::~CWUTest()
{
}

void CWUTest::init(const std::string& t_testTopic) {
	m_testTopic = t_testTopic;
}

void CWUTest::test(const std::string& t_testSubject, const bool& t_testResult) {
	t_testResult ? m_passTest++ : m_failTest++;
	std::string str = t_testSubject + (t_testResult ? " Pass" : " Fail");
	Logger::instance()->Log(Logger::INFO, str);
}

void CWUTest::report() const {
	std::string str = "---" + m_testTopic + "---\n" +
		std::to_string(m_passTest) + " pass(es)\n" +
		std::to_string(m_failTest) + " fail(s)\n";
	Logger::instance()->Log(Logger::INFO, str);
}