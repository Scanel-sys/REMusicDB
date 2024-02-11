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