#include "updater.h"

void updateApp(std::string new_version) {
	std::string oldPath = std::filesystem::current_path().string() + "\\RLpacks.exe";
	std::string newPath = std::filesystem::current_path().string() + "\\RLpacks_old.exe";
	
	std::filesystem::rename(oldPath, newPath);
	
	TCHAR location[256];
	_tcscpy_s(location, CA2T(oldPath.c_str()));

	HRESULT hr;
	LPCTSTR Url = _T("https://github.com/CopyandPaste-png/RLpacks/raw/master/RLpacks.exe"), //NEW VERSION
	File = location;

	hr = URLDownloadToFile(0, Url, File, 0, 0);
	switch (hr)
	{
	case S_OK:
		std::cout << "Successful download\n";
		write_to_file_Version(new_version);
		startNewProcess();
		break;
	case E_OUTOFMEMORY:
		std::cout << "Out of memory error\n";
		break;
	case INET_E_DOWNLOAD_FAILURE:
		std::cout << "Cannot access server data\n";
		break;
	default:
		std::cout << "Unknown error\n";
		break;
	}
}

void startNewProcess() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!
		CreateProcess
		(
			TEXT("RLpacks.exe"),
			NULL, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE,
			NULL, NULL,
			&si,
			&pi
		)
		)
	{
		std::cout << "Unable to execute.";
	}
	exit(0);
}

std::string getLastestVersion() {
	return postgres::getGUIVersion();
}