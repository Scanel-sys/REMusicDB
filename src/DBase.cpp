#include "DBase.h"


MusicItemsDB::MusicItemsDB()
{

}

MusicItemsDB::~MusicItemsDB()
{

}

void MusicItemsDB::createCategory(std::string category_name)
{
	InstrumentCategory new_category(category_name);
	this->categories_.push_back(new_category);
}

void MusicItemsDB::deleteCategory(std::vector<InstrumentCategory>::iterator category_to_delete)
{
	this->categories_.erase(category_to_delete);
}

void MusicItemsDB::addItem(Instrument& new_instrument)
{

}

std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> MusicItemsDB::findItem(std::string model_name)
{
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> output;
	output.second = false;

	for (uint8_t i = 0; i < this->getCategoriesNumber() && output.second == false; i++)
	{
		InstrumentCategory& temp_category = this->categories_[i];
		output.first = temp_category.findItem(model_name);

		if (temp_category.ifItemExist(output.first))
			output.second = true;
	}
	return output;
}

std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> MusicItemsDB::findItem(std::string company_name, std::string model_name)
{
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> output;
	output.second = false;

	for (uint8_t i = 0; i < this->getCategoriesNumber() && output.second == false; i++)
	{
		InstrumentCategory& temp_category = this->categories_[i];
		output.first = temp_category.findItem(company_name, model_name);
	
		if (temp_category.ifItemExist(output.first))
			output.second = true;
	}
	return output;
}

size_t MusicItemsDB::getCategoriesNumber()
{
	return this->categories_.size();
}
