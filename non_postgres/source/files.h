#pragma once
#pragma warning(disable : 4996)
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "wx/wx.h"
#include "logging.h"

class files {
public:
	static void write_to_file_Version(std::string version);
	static std::string readCurrentVersionFile();
	static void createInfoFile(int process);
	static std::vector<std::string> getInfo();
	static void itemsToFile(bool a, bool b);
	static bool autoUpdateEnabled();
	
};