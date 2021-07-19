#include "logging.h"
#define NEWLINE logFile << "\n";logFile << "[" << (this->getCurrentTime()) << "]"


logging::logging(std::string fileName)
{
	logFile = std::ofstream(fileName, std::ios_base::app);
}

void logging::status_insert(std::string statusMessage)
{
	NEWLINE;
	logFile << "Inserting succesful:" << statusMessage;
}

void logging::status_start()
{
	NEWLINE;
	logFile << "App started";
}

void logging::status_end()
{
	NEWLINE;
	logFile << "App ended";
	logFile << "\n";
}

void logging::status_searchError(int errorNum)
{
	switch(errorNum) {
	case 1: 
	{
		NEWLINE;
		logFile << "searchError1";
	}
	case 2: 
	{
		NEWLINE;
		logFile << "searchError2";
	}
	}	
}

void logging::status_insertError(int errorNum)
{
	switch (errorNum) {
	case 1: 
	{
		NEWLINE;
		logFile << "insertError1";
	}
	case 2: 
	{
		NEWLINE;
		logFile << "insertError2";
	}
	}
}
void logging::status_versionError(int errorNum)
{
	switch (errorNum) {
	case 1:
	{
		NEWLINE;
		logFile << "versionError1";
	}
	case 2:
	{
		NEWLINE;
		logFile << "versionError2";
	}
	}
}
void logging::customLog(std::string message)
{
	NEWLINE;
	logFile << message;

}
std::string logging::getCurrentTime()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::string currentTime = std::to_string(ltm->tm_mday) + "-"+ std::to_string(1 + ltm->tm_mon) + \
		" "+std::to_string(ltm->tm_hour) +":" +std::to_string(ltm->tm_min) +":"+ std::to_string(ltm->tm_sec);

	return currentTime;
}
