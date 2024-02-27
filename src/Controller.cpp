#include "Controller.h"

std::vector<std::vector<std::string>> Controller::takeItemsFromFile(fs::path filename)
{
	std::vector<std::vector<std::string>> output;
	std::vector<std::string> temp_item_data;

	std::fstream input_file{ filename };
	std::string line;
	while (std::getline(input_file, line))
	{
		
		if(!line.empty())
			temp_item_data.push_back(line);
		if (line.empty() && !temp_item_data.empty() || input_file.peek() == EOF)
		{
			output.push_back(temp_item_data);
			temp_item_data.clear();
		}
	}
	input_file.close();
	return output;
}

Controller::Controller(MusicItemsDB* database, View* view)
{
	this->view_ = view;
	this->database_model_ = database;
}

void Controller::launch()
{
	bool programm_is_working = true;
	while (programm_is_working)
	{
		view_->showMainMenu();
		view_->printUserInputRequest();
		this->takeUserInput();
		
		if (data_buffer == "1")
			this->takeNewItemsFromFile();

		else if (data_buffer == "2")
			this->addManualy();

		else if (data_buffer == "3")
			this->scrollDataBase();

		else if (data_buffer == "4")
			this->eraseDatabase();

		else if (data_buffer == "5" || data_buffer == "q")
		{
			this->saveDataToFile();
			programm_is_working = false;
		}
	}
}

std::string Controller::takeUserInput()
{
	data_buffer.clear();
	std::getline(std::cin, data_buffer);
	return data_buffer;
}

std::vector <std::string> Controller::takeUserInputManyTimes(std::vector<std::string>& fields_to_answer)
{
	view_->clearScreen();
	std::vector <std::string> output;
	for (int i = 0; i < fields_to_answer.size(); i++)
	{
		view_->printUserRequest(fields_to_answer[i]);
		output.push_back(takeUserInput());
	}
	return output;
}

void Controller::takeNewItemsFromFile()
{
	std::string user_output = "dummy";
	std::string input_file_name_request{ "input filename (q for quit): " };
	bool file_read = false;

	while (user_output != "q" && !file_read)
	{
		view_->clearScreen();
		view_->printUserRequest(input_file_name_request);
		user_output = this->takeUserInput();
		if (user_output == "q")
			return;

		fs::path input_file_path{ user_output };
		if (fs::is_regular_file(input_file_path))
		{
			std::vector<std::vector<std::string>> items_to_add = takeItemsFromFile(input_file_path);
			for (int i = 0; i < items_to_add.size(); i++)
				database_model_->requestItemAdding(items_to_add[i]);
			file_read = true;
		}
	}
}

void Controller::addManualy()
{
	bool user_go_back = false;
	Instrument* temp_instance = nullptr;
	std::vector <std::string> record_fields, new_item_data;
	while (!user_go_back)
	{
		view_->showPossibleInstruments();
		view_->printUserInputRequest();
		this->takeUserInput();

		user_go_back = data_buffer == "q";
		if (user_go_back)
			break;

		if (data_buffer == "1")
		{
			new_item_data.push_back("guitar");
			temp_instance = this->database_model_->getDummyInstance("guitar");
		}
		else if(data_buffer == "2")
		{
			new_item_data.push_back("bass guitar");
			temp_instance = this->database_model_->getDummyInstance("bass guitar");
		}
		else if (data_buffer == "3")
		{
			new_item_data.push_back("keyboard");
			temp_instance = this->database_model_->getDummyInstance("keyboard");
		}

		if (temp_instance != nullptr)
		{
			record_fields = temp_instance->takeRecordFieldsStrings();
			std::vector <std::string> user_input = takeUserInputManyTimes(record_fields);
			new_item_data.insert(new_item_data.end(), user_input.begin(), user_input.end());

			database_model_->requestItemAdding(new_item_data);
			delete temp_instance;
		}
	}
}

void Controller::scrollDataBase()
{

}

void Controller::eraseDatabase()
{
	database_model_->eraseDatabase();
	fs::path database_file{ "dbase_data.txt" };
	if (fs::exists(database_file)) 
		fs::remove(database_file);
}

void Controller::saveDataToFile()
{

}
