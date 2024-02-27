#pragma once
#include <iostream>
#include <Windows.h>
#include "DBase.h"

class View
{
private:
	std::vector<std::string> main_menu_strings_{ "| Pass items from file" ,
													"| Hand item adding",
													"| Scroll the Data Base",
													"| Erase database",
													"| Exit"};
	std::vector<std::string> possible_instruments{ "| Guitar" ,
													"| Bass guitar",
													"| Keyboard"};

	void printSeparatingLine();

public:
	void clearScreen();
	void printUserInputRequest();
	void printUserRequest(const std::string& request);
	void showMainMenu();
	void showPossibleInstruments();

};