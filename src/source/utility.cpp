#include "utility.h"


std::vector<std::string> utility :: split_by_newline(std::string str) {
	auto result = std::vector<std::string>{};
	auto ss = std::stringstream{ str };

	for (std::string line; std::getline(ss, line, '\n');)
		result.push_back(line);

	return result;
}

bool utility :: CopyTextToClipboard(const wxString& strVal)
{
	//copys to clipboard
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(strVal));
		wxTheClipboard->Close();
		return true;
	}
	else {
		return false;
	}
}


