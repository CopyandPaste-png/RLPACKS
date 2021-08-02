#include "web.h"

size_t web:: callBack(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string web:: ghPacks() {
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* easyhandle = curl_easy_init();
	std::string readPack;

	curl_easy_setopt(easyhandle, CURLOPT_URL, "https://raw.githubusercontent.com/CopyandPaste-png/RLpacks/master/non_postgres/packs.txt");
	//curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
	//curl_easy_setopt(easyhandle, CURLOPT_PROXY, "http://my.proxy.net");   // replace with your actual proxy
	//curl_easy_setopt(easyhandle, CURLOPT_PROXYPORT, 8080L);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, callBack);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readPack);

	curl_easy_perform(easyhandle);

	return readPack;
}

std::string web :: ghVersion() {
	curl_global_init(CURL_GLOBAL_ALL);

	CURL* easyhandle = curl_easy_init();
	std::string readVersion;

	curl_easy_setopt(easyhandle, CURLOPT_URL, "https://raw.githubusercontent.com/CopyandPaste-png/RLpacks/master/non_postgres/version.txt");
	//curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
	//curl_easy_setopt(easyhandle, CURLOPT_PROXY, "http://my.proxy.net");   // replace with your actual proxy
	//curl_easy_setopt(easyhandle, CURLOPT_PROXYPORT, 8080L);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, callBack);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readVersion);
	curl_easy_perform(easyhandle);

	return readVersion;
}
