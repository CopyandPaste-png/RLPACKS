#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "wx/wx.h"
#include "logging.h"

//version
void write_to_file_Version( std::string version);
std::string readCurrentVersionFile();
void createInfoFile(int process);

//set checkboxes(info.txt)
std::vector<std::string> getInfo();
void itemsToFile(bool a, bool b);
//Update checkboxes
