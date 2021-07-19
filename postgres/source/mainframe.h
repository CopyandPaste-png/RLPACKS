#pragma once
#include <wx/wx.h>
#include <memory.h>
#include <vector>
#include <wx/clipbrd.h>
#include "logging.h"
#include "files.h"
#include "updater.h"
#include <thread>

class mainframe : public wxFrame
{
public:
	mainframe();
	~mainframe();
	
	//unique ptrs/ components
	
	//Box
	std::unique_ptr<wxListBox>mbox;

	//Text areas
	std::unique_ptr<wxTextCtrl>searchingTerm;
	std::unique_ptr<wxTextCtrl>searchingTag;
	std::unique_ptr<wxTextCtrl>insertingName;
	std::unique_ptr<wxTextCtrl>insertingCode;
	std::unique_ptr<wxTextCtrl>insertingTag;
	std::unique_ptr<wxTextCtrl>status;
	std::unique_ptr<wxStaticText>version;

	//Buttons
	std::unique_ptr<wxButton>search;
	std::unique_ptr<wxButton>clear;
	std::unique_ptr<wxButton>insert;

	//Message box for update
	std::unique_ptr<wxMessageDialog>popup;

	//Functions for events
	void OnButtonClicked_search(wxCommandEvent& evt);
	void OnButtonClicked_clear(wxCommandEvent& evt);
	void OnButtonClicked_insert(wxCommandEvent& evt);
	void OnListElementSelected(wxCommandEvent& evt);
	void showPopUp(std::string newVersion);


};

