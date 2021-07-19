#include "links.h"


links::links() : wxFrame(nullptr, wxID_ANY, "Links", wxPoint(200, 200), wxSize(200, 200))
{
	//Defines a font
	wxFont font_1(wxFontInfo(16).FaceName("Arial").Underlined().Bold());

	//Sets github link and font
	github = std::unique_ptr<wxHyperlinkCtrl>(new wxHyperlinkCtrl(this, 51, "Github", "https://github.com/CopyandPaste-png/RLPACKS", wxPoint(50, 50), wxSize(150, 30)));
	github->SetFont(font_1);

	//Sets discord link and font
	discord = std::unique_ptr<wxHyperlinkCtrl>(new wxHyperlinkCtrl(this, 51, "Discord", "https://discord.gg/Z9KW3ZPtJt", wxPoint(50, 100), wxSize(150, 30)));
	discord->SetFont(font_1);

}

links::~links()
{
}