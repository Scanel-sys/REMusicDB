#pragma once

#include "InstrumentCategory.h"

#include <vector>
#include <string>


class MusicItemsDB
{
private:
	std::vector <InstrumentCategory> categories_;

public:

	MusicItemsDB();
	~MusicItemsDB();

	void createCategory(std::string category_name);
	void deleteCategory(std::vector<InstrumentCategory>::iterator category_to_delete);

	void addItem(Instrument& new_instrument);
	void findItem(std::string model_name);
	void findItem(std::string company_name, std::string model_name);

};
