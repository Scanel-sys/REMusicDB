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

	std::string data_buffer;

	std::vector<std::vector<std::string>> takeItemsFromFile(fs::path filename);

public:
	Controller(MusicItemsDB* database, View* view);
	void launch();
	std::string takeUserInput();
	std::vector <std::string> takeUserInputManyTimes(std::vector<std::string>& fields_to_answer);

	void takeNewItemsFromFile();
	void addManualy();
	void scrollDataBase();
	void eraseDatabase();
	void saveDataToFile();
};