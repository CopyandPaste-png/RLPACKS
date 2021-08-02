#pragma once
#pragma warning(disable : 4996)
#include <string>
#include <fstream>

class logging
{
public:
	logging(std::string fileName);
public:
	void status_insert(std::string statusMessage);
	void status_start();
	void status_end();
	void customLog(std::string message);
	std::string getCurrentTime();
	std::string logFile;
};

