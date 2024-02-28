#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>

#include "View.h"

namespace fs = std::filesystem;


class Controller 
{
private:
	const std::string default_filename{"db_output.txt"};
	View* view_;
	MusicItemsDB* database_model_;

	std::string msg;
	std::string data_buffer;

	std::vector<std::vector<std::string>> takeItemsFromFile(fs::path filename);
	std::vector<std::vector<std::string>> prepareItemsForFileWrite();
	void writeDataToFile(fs::path filename, std::vector<std::vector<std::string>> data_to_write);
	
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
	void handleStocking();

public:
	Controller(MusicItemsDB* database, View* view);
	void launch();
};