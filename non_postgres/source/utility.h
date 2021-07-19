#pragma once
#include <wx/string.h>
#include <wx/clipbrd.h>
#include <vector>
#include <string>
#include <sstream>


class utility {
public:
	static std::vector<std::string> split_by_newline(std::string str);
	static bool CopyTextToClipboard(const wxString& strVal);
};
