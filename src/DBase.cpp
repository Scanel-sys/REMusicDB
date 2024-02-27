#include "DBase.h"


void MusicItemsDB::addToStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, std::vector<std::string>& item_data)
{
	unsigned long items_count = std::stoul(item_data[3]);
	item_iter->get().addToStock(items_count);
}

void MusicItemsDB::stockNewItem(std::vector<std::string>& item_data)
{
	std::string item_type = item_data[0];
	Instrument* validator_instance = getDummyInstance(item_type);
	if (validator_instance->isValidData(item_data))
	{
		Instrument* item_instance = getInstance(item_data);
		std::pair<std::vector<InstrumentCategory>::iterator, bool> category = findCategory(item_type);
		if (!category.second)
		{
			category.first = this->createCategory(item_type);
			category.second = true;
		}
		category.first->addItem(*item_instance);
	}
	delete validator_instance;
}

MusicItemsDB::MusicItemsDB()
{
	this->items_class_handlers_["guitar"] = &createInstance<Guitar>;
	this->items_class_handlers_["keyboard"] = &createInstance<Keyboard>;
	this->items_class_handlers_["bass guitar"] = &createInstance<Bass>;

	this->dummy_class_handlers_["guitar"] = &createDummyInstance<Guitar>;
	this->dummy_class_handlers_["keyboard"] = &createDummyInstance<Keyboard>;
	this->dummy_class_handlers_["bass guitar"] = &createDummyInstance<Bass>;
}

MusicItemsDB::~MusicItemsDB()
{
	this->items_class_handlers_.clear();
	this->dummy_class_handlers_.clear();
}

std::vector<InstrumentCategory>::iterator MusicItemsDB::createCategory(std::string category_name)
{
	InstrumentCategory new_category(category_name);
	this->categories_.push_back(new_category);
	return std::prev(this->categories_.end());
}

void MusicItemsDB::deleteCategory(std::vector<InstrumentCategory>::iterator category_to_delete)
{
	this->categories_.erase(category_to_delete);
}

void MusicItemsDB::eraseDatabase()
{
	this->categories_.clear();
}

void MusicItemsDB::requestItemAdding(std::vector <std::string>& item_data)
{
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> find_result;
	std::string company_name = item_data[0];
	std::string model_name = item_data[1];
	find_result = this->findItem(company_name, model_name);

	if (find_result.second)
	{
		this->addToStock(find_result.first, item_data);
	}
	else
	{
		this->stockNewItem(item_data);
	}

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

std::pair<std::vector<InstrumentCategory>::iterator, bool> MusicItemsDB::findCategory(std::string category_name)
{
	std::pair<std::vector<InstrumentCategory>::iterator, bool> output;
	output.first = this->getCategoryIterator(category_name);
	output.second = output.first != this->categories_.end();
	return output;
}

std::vector<InstrumentCategory>::iterator MusicItemsDB::getCategoryIterator(std::string category_name)
{
	return std::find_if(this->categories_.begin(), this->categories_.end(),
		[category_name](InstrumentCategory& temp_category) -> bool
		{ return temp_category.getCategoryName()  == category_name; });
}


size_t MusicItemsDB::getCategoriesNumber()
{
	return this->categories_.size();
}

Instrument* MusicItemsDB::getDummyInstance(const std::string& instrument_name)
{
	return dummy_class_handlers_[instrument_name]();
}

Instrument* MusicItemsDB::getInstance(const std::vector<std::string>& item_data)
{
	return items_class_handlers_[item_data[0]](item_data);
}
