#pragma once

#include "Instrument.h"

#include <string>
#include <vector>


class InstrumentCategory
{

private:
	std::string category_name_;
	std::vector <Instrument> items_;

public:
	InstrumentCategory(std::string category_name);
	~InstrumentCategory();

	std::string getCategoryName();

	void addItem(Instrument &new_instrument);

	std::vector<Instrument>::iterator findItem(std::string model_name);
	std::vector<Instrument>::iterator findItem(std::string company_name, std::string model_name);

	
};