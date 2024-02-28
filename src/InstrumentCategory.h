#pragma once

#include "Instrument.h"

#include <string>
#include <vector>
#include <functional>


class InstrumentCategory
{

private:
	std::string category_name_;
	std::vector <std::reference_wrapper<Instrument>> items_;

public:
	InstrumentCategory(std::string category_name);
	~InstrumentCategory();

	std::string getCategoryName();
	unsigned long size();
	bool empty();

	void addItem(Instrument &new_instrument);
	bool ifItemExist(std::vector< std::reference_wrapper<Instrument>>::iterator result);

	std::vector< std::reference_wrapper<Instrument>>::iterator findItem(std::string model_name);
	std::vector< std::reference_wrapper<Instrument>>::iterator findItem(std::string company_name, std::string model_name);

	std::vector <std::reference_wrapper<Instrument>>::iterator getFirstItemsIterator();
	std::vector <std::reference_wrapper<Instrument>>::iterator getLastItemsIterator();
};