#pragma once
#pragma warning(disable : 4996)
#include <string>
#include <fstream>


class logging
{
	
public:
	logging(std::string fileName);
	~logging() {
		logFile.close();
	};

public:
	void status_insert(std::string statusMessage);
	void status_start();
	void status_end();
	void status_searchError(int errorNum);
	void status_insertError(int errorNum);
	void status_versionError(int errorNum);
	void customLog(std::string message);
	std::ofstream logFile;
	std::string getCurrentTime();

	void close() {
		logging::~logging();
	}
};

