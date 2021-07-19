#include "GUI.h"


IMPLEMENT_APP(GUI)


void GUI::settingCheckBoxes()
{
	//unordered map
	std::unordered_map<int, int>menuItems;

	std::pair<int, int>input1(0, 60); // auto update
	std::pair<int, int>input2(1, 61); // max search

	menuItems.insert(input1);
	menuItems.insert(input2);

	std::vector<std::string>info = files::getInfo();

	int n = 0;
	int size = info.size();
	
	if (size < 2)
	{
		autoUpdateSetting = false;
		maxResultsSetting = false;
		return;
	}
	else
	{
		for (int i = 0; i < size; i++) {
			if (info.at(i) == "1") {
				settingMenu->Check(menuItems.at(n), true);
				n++;

			}
			else {
				settingMenu->Check(menuItems.at(n), false);
				n++;
			}
		}

		(info.at(0) == "1") ? autoUpdateSetting = true : autoUpdateSetting = false;
		(info.at(1) == "1") ? maxResultsSetting = true : maxResultsSetting = false;

	}

}


bool GUI::OnInit()
{
	this->Logger = std::unique_ptr<logging>(new logging("log.txt"));

	std::ofstream file("log.txt", std::fstream::out | std::fstream::trunc);
	file.close();

	std::ofstream packs("packs.txt");
	auto ss = std::stringstream{ web::ghPacks() };

	for (std::string line; std::getline(ss, line, '\n');)
		packs << line << "\n";

	
	//update app (check version->if not the same then update)
	
	if (Updater->versionsEqual() && files::autoUpdateEnabled()) {
		Logger->customLog("Updated to " + web::ghPacks());
		Updater->updateApp(web::ghPacks());
	}
		
	//Init

	if (std::filesystem::exists("RLpacks_old.exe")) {
		const char* filename = "RLpacks_old.exe";
		std::remove(filename);
		Logger->customLog("Removed old version");
	}
	
	Logger->status_start();


	menuBar = new wxMenuBar();
	helpMenu = new wxMenu();
	settingMenu = new wxMenu();

	//Apending menu items
	helpMenu->Append(001, "&Links");
	helpMenu->Append(002, "&About");
	helpMenu->Append(003, "&Setting");


	settingMenu->AppendCheckItem(60, "Auto Update", "");
	settingMenu->AppendCheckItem(61, "Max limit", "");

	
	settingCheckBoxes();


	//Events

	Bind(wxEVT_MENU, &GUI::websites, this, 001);
	Bind(wxEVT_MENU, &GUI::settingCheckBoxesAutoUpdate, this, 60);
	Bind(wxEVT_MENU, &GUI::settingCheckBoxesMax, this, 61);

	//Bind menu subs to menu
	menuBar->Append(helpMenu, _T("&Help"));
	menuBar->Append(settingMenu, _T("&Setting"));
	

	//Create new frame
	mframe = std::unique_ptr<mainframe>(new mainframe());

	//Set menu bar
	mframe->SetMenuBar(menuBar);

	//Show the frame
	mframe->Show();

	return true;
}


void GUI::websites(wxCommandEvent& evt)
{
	//Creates new links frame
	links_bar = std::unique_ptr<links>(new links());

	//Shows frame
	links_bar->Show();

	//Skips event. No need to go up higher in event hierarchy
	evt.Skip();
}

void GUI::settingCheckBoxesAutoUpdate(wxCommandEvent& evt)
{
	autoUpdateSetting = !(autoUpdateSetting);
}

void GUI::settingCheckBoxesMax(wxCommandEvent& evt) {
	maxResultsSetting = !(maxResultsSetting);
}

void GUI::endProcesses() {

	Logger->status_end();
	files::itemsToFile(autoUpdateSetting, maxResultsSetting);
}

int GUI::OnExit()
{
	endProcesses();
	//garbage collection
	delete helpMenu;
	delete menuBar;
	delete settingMenu;
	return 0;
}