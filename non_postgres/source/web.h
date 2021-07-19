#pragma once
#include <curl/curl.h>
#include <string>

class web {
public:
	static size_t callBack(char* contents, size_t size, size_t nmemb, void* userp);
	static std::string ghPacks();
	static std::string ghVersion();
};
