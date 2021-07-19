#pragma once
#include<iostream>
#include <filesystem>
#include<windows.h>
#include <Windows.h>
#include <tchar.h>
#include <urlmon.h>
#include <string>
#include <atlstr.h>
#include "files.h"
#include <tlhelp32.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "postgresSQL.lib")

#include "postgresfunc.h"
#include "post_exceptions.h"

void updateApp(std::string new_version);
void startNewProcess();
std::string getLastestVersion();