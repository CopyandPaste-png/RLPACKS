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
#include "web.h"
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")

class update {
public:
	update();
	void updateApp(std::string new_version);
	void startNewProcess();
	bool versionsEqual();

private:
	std::unique_ptr<logging>Logger;
};