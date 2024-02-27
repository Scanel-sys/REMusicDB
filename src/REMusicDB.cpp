#include "DBase.h"
#include "View.h"
#include "Controller.h"

#include <iostream>

/*
	TODO:
		> write controller what will takes user input and handle it
			> validate user input
			> work with files (dbase should build itself with taken files
								or controller should build bd?)

		> view what will take info from "prepareItemInfo" methods and put it out
			> also output user menu

*/


int main()
{
	MusicItemsDB database;
	View view;
	Controller controller(&database, &view);
	controller.launch();
}