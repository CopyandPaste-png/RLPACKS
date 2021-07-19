#pragma once
#include "mainframe.h"
#include "links.h"
#include <wx/menuitem.h>
#include <wx/checkbox.h>

//#include "logging.h" is taken from mainframe.h

class GUI : public wxApp
{
public:
	GUI();
	virtual bool OnInit();
	int OnExit();
	
	

public:
	//Unique ptrs
	std::unique_ptr<mainframe>mframe;
	std::unique_ptr<links>links_bar;

	//Vectors
	std::vector<std::string> labels = { "&Links", "&About"};

	//Menu
	std::unique_ptr<wxCheckBox> checkbox;
	//Raw pointers
	wxMenuBar* menuBar = nullptr;
	wxMenu* helpMenu = nullptr;
	wxMenu* settingMenu = nullptr;

	//bools
	bool maxResultsSetting;
	bool autoUpdateSetting;
	
	//functions
	void websites(wxCommandEvent& evt);
	void settingCheckBoxesAutoUpdate(wxCommandEvent& evt);
	void settingCheckBoxesMax(wxCommandEvent& evt);
	void settingCheckBoxes(); 
	void endProcesses();


};

