// SimpleLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "CWStd.hpp"
#include "CWUTest.hpp"
#include "Logger.hpp"

#define _CRTDBG_MAP_ALLOC

float calSquareArea(float t_w) {
	// What are valid values
	if (!(t_w >= 0.0f && t_w <= std::sqrtf(std::numeric_limits<float>::max()))) {
		Logger::instance()->Log(Logger::ERROR, "This Value must be greater than zero");
	}
	REQUIRED(t_w >= 0.0f && t_w <= std::sqrtf(std::numeric_limits<float>::max()));

	float area = 0.0f;

	if (t_w > 0.0f) {
		area = t_w * t_w;
	}
	if (t_w == 0.0f) {
		Logger::instance()->Log(Logger::INFO, "This Value must be greater than zero");
	}
	PROMISED(area >= 0.0f);
	return area;
}

std::string readLastLine() {
	std::ifstream testLogFile;
	testLogFile.open("error.log", std::ios::in | std::ios::ate);
	REQUIRED(testLogFile);
	REQUIRED(testLogFile.is_open());
	testLogFile.seekg(-1, std::ios_base::end);

	bool keepLooping = true;
	unsigned int c = 0;
	while (keepLooping) {
		char ch;
		
		testLogFile.get(ch);
		if (static_cast<int>(testLogFile.tellg()) <= 1) {
			testLogFile.seekg(0, std::ios_base::beg);
			keepLooping = false;
		}
		else if (ch == '\n') {
			c++;
			if (c == 2) {
				keepLooping = false;
				break;
			}
			testLogFile.seekg(-3, std::ios_base::cur);
		}
		else {
			testLogFile.seekg(-2, std::ios_base::cur);
		}
	}

	std::string lastLine;
	getline(testLogFile, lastLine);
	testLogFile.close();
	return lastLine;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	std::string str = "Hello Log";
	CWUTest ut;
	ut.init("Test Logger function");
	
	Logger::instance()->Log(Logger::INFO, str);
	ut.test("Write Log [INFO] " + str, readLastLine() == "[INFO] " + str);

	ut.test("calSquareArea(5.0f) == 25.0f", calSquareArea(5.0f) == 25.0f);
	ut.test("calSquareArea(0.0f) == 0.0f", calSquareArea(0.0f) == 0.0f);
	// Error Log
	//ut.test("calSquareArea(-1.0f) == 0.0f", calSquareArea(-1.0f) == 0.0f);
	ut.test("Write Log [INFO] calSquareArea(0.0f) == 0.0f Pass", readLastLine() == "[INFO] calSquareArea(0.0f) == 0.0f Pass");

	Logger::releaseInstance();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
