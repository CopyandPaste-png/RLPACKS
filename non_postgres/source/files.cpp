#include "files.h"

//Version
void files::write_to_file_Version( std::string version)
{
	std::ofstream versionFile ("GUIversion.txt", std::ios::trunc);
	
	versionFile << version;

	versionFile.close();

}

std::string  files::readCurrentVersionFile() {
	
	std::string version;
	std::ifstream versionFile("GUIversion.txt");
	std::string errorMessage = "NEVER GONNA GIVE YOU UP.NEVER GONNA TURN AROUND BABY";

	if (!versionFile) {
		versionFile.close();
		std::ofstream versionFile("GUIversion.txt");
		logging Logger("log.txt");
		Logger.customLog("new version file created");
		versionFile << "1.0.0";
		versionFile.close();
		return errorMessage;
	}

	getline(versionFile, version);
	versionFile.close();
	return version;
}

//Info

void  files::createInfoFile(int process)
{
	
	switch (process)
	{
	case 0:
	{
		std::ofstream file(std::filesystem::current_path().string() + "/info.txt");
		file << "0" << "\n" << "0";
		file.close();
		break; 
	}
	case 1:
	{
		break; 
	}
	}
}

// Get infos
std::vector<std::string>  files::getInfo()
{
	std::ifstream versionFile(std::filesystem::current_path().string() + "/info.txt");

	(!versionFile)? createInfoFile(0): createInfoFile(1);

	std::string line;

	std::vector<std::string>info;

	while (std::getline(versionFile, line))
	{
		info.push_back(line);
	}

	versionFile.close();
	return info;

}

void  files::itemsToFile(bool a, bool b)
{
	std::ofstream infoFile("info.txt");

	infoFile << a << "\n";
	infoFile << b;

	infoFile.close();
}


bool files::autoUpdateEnabled() {
	std::vector<std::string>info = getInfo();

	int size = info.size();

	if (size < 1)
	{
		return false;
	}
	else {
		if (info.at(0) == '1')
			return true;
	}
}
