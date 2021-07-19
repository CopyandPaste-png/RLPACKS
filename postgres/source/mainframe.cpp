#include "mainframe.h"


mainframe::mainframe() : wxFrame(nullptr, wxID_ANY, "Rocket League GUI", wxPoint(30, 30), wxSize(800, 600))
{
	
	//Create box
	mbox = std::unique_ptr<wxListBox>(new wxListBox(this, 23, wxPoint(10, 10), wxSize(300, 500)));
	mbox->Append("Results appear here");
	//Create text area for user input
	
	//searching
	searchingTerm = std::unique_ptr<wxTextCtrl>(new wxTextCtrl(this, 10, wxString("Enter search term here"), wxPoint(340, 30), wxSize(195, 30)));
	searchingTag = std::unique_ptr<wxTextCtrl>(new wxTextCtrl(this, 11, wxString("Enter tag term here"), wxPoint(340, 60), wxSize(195, 30)));

	//inserting
	insertingName = std::unique_ptr<wxTextCtrl>(new wxTextCtrl(this, 12, wxString("Enter name of pack"), wxPoint(340, 200), wxSize(195, 30)));
	insertingCode = std::unique_ptr<wxTextCtrl>(new wxTextCtrl(this, 13, wxString("Enter code of pack"), wxPoint(340, 230), wxSize(195, 30)));
	insertingTag = std::unique_ptr<wxTextCtrl>(new wxTextCtrl(this, 14, wxString("Enter tags of pack(seperated by ',')"), wxPoint(340, 260), wxSize(195, 30)));

	//status
	//wxTE_READONLY
	status = std::unique_ptr<wxTextCtrl>(new wxTextCtrl(this, 15, wxString("Status of events here"), wxPoint(340, 400), wxSize(250, 30), wxTE_READONLY));

	//version
	version = std::unique_ptr<wxStaticText>(new wxStaticText(this,16,wxString("Version:"+ readCurrentVersionFile()),wxPoint(700,500),wxSize(150,75)));
	//Create buttons
	search = std::unique_ptr<wxButton>(new wxButton(this, 20, "search", wxPoint(340, 120), wxSize(100, 30)));
	clear = std::unique_ptr<wxButton>(new wxButton(this, 21, "clear", wxPoint(340, 150), wxSize(100, 30)));
	insert = std::unique_ptr<wxButton>(new wxButton(this, 22, "insert", wxPoint(340, 320), wxSize(100, 30))); 
	

	//Binding
	Bind(wxEVT_BUTTON, &mainframe::OnButtonClicked_search,this, 20);
	Bind(wxEVT_BUTTON, &mainframe::OnButtonClicked_clear,this, 21);
	Bind(wxEVT_BUTTON, &mainframe::OnButtonClicked_insert,this, 22);
	Bind(wxEVT_LISTBOX, &mainframe::OnListElementSelected,this, 23);
	
	if (readCurrentVersionFile() != getLastestVersion()) {
		showPopUp(getLastestVersion());
	}
}

mainframe:: ~mainframe() {}

void mainframe::showPopUp(std::string newVersion){
	int dialog_return_value = wxNO;
	popup = std::unique_ptr<wxMessageDialog>(new wxMessageDialog(this, "There is an update to version " + newVersion + "\nDo you want to download it now?", "", wxYES_NO | wxNO_DEFAULT));
	dialog_return_value = popup->ShowModal();
	status->SetValue(std::to_string(dialog_return_value));


	// int for wxNo is 5104
	// int for wxYes is 5103
	
	switch (dialog_return_value) // Use switch, scales to more buttons later
	{
	case 5104: /*When no is pressed*/
		break; 
	case 5103:/*When yes is pressed*/ {
		logging Logger("log.txt");
		Logger.customLog("Updated to " + newVersion);
		updateApp(newVersion);
		break; }
	default:
		break;/* ignore or handle error */;
	};

}
void mainframe::OnButtonClicked_search(wxCommandEvent& evt)
{
	// In case both search and tag fields are empty, all entries are called.
	//This limits it to only 100 entries to be displayed
	int max = 100;


	//Called when "search" button is clicked
 
	//Clears any last search results
	mbox->Clear();

	//Gets value from "Search term" box
	wxString value = searchingTerm->GetValue();

	//Converts to std::string
	std::string search_term = std::string(value.mb_str());

	//Same process but for Tag term
	wxString value1 = searchingTag->GetValue();
	std::string tag_term = std::string(value.mb_str());
	
	//declare vector
	std::vector<std::string> packs;

	//Gets results
	
	try {
		std::vector<std::string> results = postgres::getGUIPacks(search_term, tag_term);

		//initialising a counter to 0
		int counter{ 0 };

		//Displays in box
		for (auto x : results)
		{
			if (counter == max)
				break;

			mbox->Append(wxString(x.substr(0, x.find_last_of(":"))));
			counter += 1;
		}
		status->Clear();
		std::string message = (counter > 0) ? "Search results:" + std::to_string(counter) + " results" : "No results";

		status->SetValue(message);

	}
	catch (searchError1 e)
	{
		logging Logger("error.txt");
		Logger.status_searchError(1);
		status->SetValue(e.error_message());
		return;
	}
	catch (searchError2 e)
	{
		logging Logger("error.txt");
		Logger.status_searchError(2);
		status->SetValue(e.error_message());
		return;
	}
	
}


void mainframe::OnButtonClicked_clear(wxCommandEvent& evt)
{
	//Clears the box and text fields
	mbox->Clear();
	searchingTerm->Clear();
	searchingTag->Clear();
	insertingName->Clear();
	insertingCode->Clear();
	insertingTag->Clear();
}


bool CopyTextToClipboard(const wxString& strVal)
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

void mainframe::OnListElementSelected(wxCommandEvent& evt)
{
	//Gets the item that the user has clicked on
	int n = mbox->GetSelection();

	//Converts from wxString->std::string
	std::string value = std::string((mbox->GetString(n)).mb_str());

	//Gets the code
	std::string result = value.substr(value.find_first_of(":") + 1,19);

	//Copies to clipboard
	CopyTextToClipboard(wxString(result));
	status->Clear();
	status->SetValue("Copied pack code:" + result);
	//evt.Skip();
}

void mainframe::OnButtonClicked_insert(wxCommandEvent& evt)
{
	//for logging
	logging Logger("log.txt");
	logging Error("error.txt");


	//Gets value from "Name" textfield
	wxString value1 = insertingName->GetValue();
	std::string name = std::string(value1.mb_str());

	//Gets values from "Code" textfield
	wxString value2 = insertingCode->GetValue();
	std::string code = std::string(value2.mb_str());

	//Gets values from "Tags" textfield
	wxString value3 = insertingTag->GetValue();
	std::string tag = std::string(value3.mb_str());

	if (tag == "Enter tags of pack(seperated by ',')")
	{
		tag.clear();
		insertingTag->SetValue("");
	}

	//Name length must be > 0
	//Code must be 19 length with 3 -'s
	//tag length can be length 0, but will be faced with a messagebox

	bool valid_code;

	(std::count(code.begin(), code.end(), '-') != 3 || code.length() != 19) ? valid_code=true : valid_code=false;

	if (name.length() == 0)
	{
		wxMessageBox("Name too short");
		status->Clear();
		status->SetValue("Inserting failed- Name invalid");

		Logger.customLog("[Inserting]Name too short:" + name);
		return;
	}
	else if (valid_code)
	{
		wxMessageBox("Code is invalid\n(Avoid whitespaces at the end of your code)");
		status->Clear();
		status->SetValue("Inserting failed-Code invalid");

		Logger.customLog("[Inserting]Code too short or invalid code:" + code);
		return;
	}
	else if (tag.length() == 0)
	{
		wxMessageBox("No tags have been entered\nThis is not an error, but might make finding your code more difficult.");


		Logger.customLog("[Inserting]No tags provided for:{" + name + "," + code + "}");
	}
	

	//Inserts code into pack
	try {
		postgres::insertPack(name, code, tag);
	}
	catch (insertError1 e) {
		
		Error.status_insertError(1);
		status->SetValue(e.error_message());
		return;
	}
	catch (insertError2 e) {
		Error.status_insertError(2);
		status->SetValue(e.error_message());
		return;
	}

	status->Clear();
	status->SetValue("Inserting pack was successful");
	

	Logger.status_insert(name + ":" + code);

	Error.close();
	Logger.close();
	//no need to go up event hierarchy
	evt.Skip();
}