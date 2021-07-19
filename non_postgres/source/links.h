#pragma once
#include "wx/wx.h"
#include <wx/hyperlink.h>
#include <vector>
#include <memory>


class links :public wxFrame
{
public:
	links();
	~links();

public:
	std::unique_ptr<wxHyperlinkCtrl>github;
	std::unique_ptr<wxHyperlinkCtrl>discord;
};
