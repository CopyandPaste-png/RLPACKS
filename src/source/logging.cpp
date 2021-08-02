#include "logging.h"
#define NEWLINE file << "\n"; file << "[" << (this->getCurrentTime()) << "]"

logging::logging(std::string fileName) 
	:logFile{ fileName } {}

void logging::status_insert(std::string statusMessage)
{
	std::ofstream file{ std::ofstream(logFile, std::ios_base::app) };
	NEWLINE;
	file << "Inserting succesful:" << statusMessage;
	file.close();
}

void logging::status_start()
{
	std::ofstream file{ std::ofstream(logFile, std::ios_base::app) };
	NEWLINE;
	file << "App started";
	file.close();
}

void logging::status_end()
{
	std::ofstream file{ std::ofstream(logFile, std::ios_base::app) };
	NEWLINE;
	file << "App ended";
	file << "\n";
	file.close();
}

void logging::customLog(std::string message)
{
	std::ofstream file{ std::ofstream(logFile, std::ios_base::app) };
	NEWLINE;
	file << message;
	file.close();

}
std::string logging::getCurrentTime()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::string currentTime = std::to_string(ltm->tm_mday) + "-"+ std::to_string(1 + ltm->tm_mon) + \
		" "+std::to_string(ltm->tm_hour) +":" +std::to_string(ltm->tm_min) +":"+ std::to_string(ltm->tm_sec);

	return currentTime;
}
