#include "InstrumentCategory.h"


InstrumentCategory::InstrumentCategory(std::string category_name)
{
	this->category_name_ = category_name;
}

InstrumentCategory::~InstrumentCategory()
{

}


std::string InstrumentCategory::getCategoryName()
{
	return this->category_name_;
}


void InstrumentCategory::addItem(Instrument &new_instrument)
{
	std::vector<std::reference_wrapper<Instrument>>::iterator found_item = this->findItem(new_instrument.getCompanyName(), new_instrument.getModelName());
	std::vector<std::reference_wrapper<Instrument>>::iterator last_category_item = this->items_.end();
	
	if (found_item != last_category_item)
	{
		found_item->get().setModelCount(found_item->get().getModelCount() + new_instrument.getModelCount());
	}
	else
	{
		this->items_.push_back(new_instrument);
	}
}

bool InstrumentCategory::ifItemExist(std::vector< std::reference_wrapper<Instrument>>::iterator result)
{
	return result != this->items_.end();
}


std::vector<std::reference_wrapper<Instrument>>::iterator InstrumentCategory::findItem(std::string model_name)
{
	return std::find_if(this->items_.begin(), this->items_.end(),
		[model_name](Instrument& item) -> bool 
		{ return item.getModelName() == model_name; });
}

std::vector< std::reference_wrapper<Instrument>>::iterator InstrumentCategory::findItem(std::string company_name, std::string model_name)
{
	return std::find_if(this->items_.begin(), this->items_.end(),
		[company_name, model_name](Instrument& item) -> bool
		{ return item.getCompanyName() == company_name && item.getModelName() == model_name;});
}