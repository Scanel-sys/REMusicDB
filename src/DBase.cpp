#include "DBase.h"


void MusicItemsDB::addToStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, std::vector<std::string>& item_data)
{
	if (isLegalUInt(item_data[COUNT_IDX]))
	{
		unsigned long items_count = std::stoul(item_data[COUNT_IDX]);
		item_iter->get().addToStock(items_count);
	}
}

void MusicItemsDB::addToStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, unsigned long add_to_stock_count)
{
	item_iter->get().addToStock(add_to_stock_count);
}
void MusicItemsDB::takeFromStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, unsigned long take_from_stock_count)
{
	item_iter->get().takeFromStock(take_from_stock_count);
}

void MusicItemsDB::stockNewItem(std::vector<std::string>& item_data)
{
	std::string item_type = item_data[INSTRUMENT_CLASS_IDX];
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

bool MusicItemsDB::isLegalUInt(std::string const& input)
{
	bool result = true;

	for (uint64_t i = 0; i < input.size() && result; i++)
		result = isdigit(input[i]);

	return result;
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
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> item_find_result;
	std::pair <std::vector <InstrumentCategory>::iterator, bool> category_iterator;
	std::string company_name = item_data[COMPANY_NAME_IDX];
	std::string model_name = item_data[MODEL_NAME_IDX];
	item_find_result = this->findItem(company_name, model_name);

	if (item_find_result.second)
	{
		this->addToStock(item_find_result.first, item_data);
	}
	else
	{
		this->stockNewItem(item_data);
	}
	category_iterator = this->findCategory(item_data[INSTRUMENT_CLASS_IDX]);
	item_find_result = this->findItem(company_name, model_name);
	if(category_iterator.second && item_find_result.second)
		this->setIterators(category_iterator.first, item_find_result.first);
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
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, volatile bool> output;
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

void MusicItemsDB::setIterators(std::vector<InstrumentCategory>::iterator category_iterator, std::vector<std::reference_wrapper<Instrument>>::iterator item_iterator)
{
	this->act_category_ = category_iterator;
	this->act_category_item_ = item_iterator;
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

std::vector<std::string> MusicItemsDB::getScrollingItemOutputData()
{
	std::vector <std::string> output;
	if (!ifScrollingCategoryEmpty())
		output = act_category_item_->get().prepareItemInfo();
	return output;
}

std::vector<std::vector<std::string>> MusicItemsDB::prepareItemsForFileWrite()
{
	std::vector<std::vector<std::string>> output;
	std::vector<std::string> temp_item_data;

	while (!this->ifFirstCategory())
		this->prevCategory();

	std::vector <InstrumentCategory>::iterator t_category = this->act_category_;
	std::vector <std::reference_wrapper<Instrument>>::iterator t_category_item = this->act_category_item_;

	while (t_category != categories_.end())
	{
		temp_item_data = t_category_item->get().prepareItemInfo();
		temp_item_data.push_back("");
		output.push_back(temp_item_data);

		if (t_category_item == t_category->getLastItemsIterator())
		{
			t_category = std::next(t_category);
			if(t_category != categories_.end())
				t_category_item = t_category->getFirstItemsIterator();
		}
		else
		{
			t_category_item = std::next(t_category_item);
		}
	} 

	return output;
}

bool MusicItemsDB::empty()
{
	return this->categories_.empty();
}

bool MusicItemsDB::ifScrollingCategoryEmpty()
{
	return this->act_category_->empty();
}

bool MusicItemsDB::ifFirstCategory()
{
	return this->act_category_ == this->categories_.begin();
}

bool MusicItemsDB::ifLastCategory()
{
	return this->act_category_ == std::prev(this->categories_.end());
}

bool MusicItemsDB::ifFirstItem()
{
	return this->act_category_item_ == this->act_category_->getFirstItemsIterator();
}

bool MusicItemsDB::ifLastItem()
{
	return this->act_category_item_ == this->act_category_->getLastItemsIterator();
}

void MusicItemsDB::nextCategory()
{
	if (!this->ifLastCategory())
	{
		act_category_ = std::next(this->act_category_);
		act_category_item_ = act_category_->getFirstItemsIterator();
	}
}

void MusicItemsDB::prevCategory()
{
	if(!this->ifFirstCategory())
	{
		act_category_ = std::prev(this->act_category_);
		act_category_item_ = act_category_->getFirstItemsIterator();
	}
}

void MusicItemsDB::nextItem()
{
	if(!this->ifLastItem())
		this->act_category_item_ = std::next(this->act_category_item_);
}

void MusicItemsDB::prevItem()
{
	if(!this->ifFirstItem())
		this->act_category_item_ = std::prev(this->act_category_item_);
}

void MusicItemsDB::stockToScrollingItem(unsigned long count)
{
	addToStock(act_category_item_, count);
}

void MusicItemsDB::takeScrollingItemFromStock(unsigned long count)
{
	takeFromStock(act_category_item_, count);
}
