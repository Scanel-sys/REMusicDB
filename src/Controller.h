#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>

#include "View.h"

namespace fs = std::filesystem;


class Controller 
{
private:
	View* view_;
	MusicItemsDB* database_model_;

	std::string msg;
	std::string data_buffer;

	std::vector<std::vector<std::string>> takeItemsFromFile(fs::path filename);

	void setMsg(std::string msg);

	std::string takeUserInput();
	std::vector <std::string> takeUserInputManyTimes(std::vector<std::string>& fields_to_answer);

	bool msg_left();
	void send_msg_to_user();

	void takeNewItemsFromFile();
	void addManualy();
	void scrollDataBase();
	void eraseDatabase();
	void saveDataToFile();

	std::vector <std::string> gatherScrollingMenu();
	void reserveSpaceForUserInput();
	void placeCursorForUserInput();

	void makeScrolling();

public:
	Controller(MusicItemsDB* database, View* view);
	void launch();
};