#pragma once

#include "InstrumentCategory.h"

#include <vector>
#include <string>
#include <map>

typedef std::map < std::string, Instrument* (*)(std::vector<std::string>) > items_class_handlers;
typedef std::map < std::string, Instrument* (*)() > dummy_class_handlers;

template<typename T> Instrument* createInstance(std::vector<std::string>) { return new T; }
template<typename T> Instrument* createDummyInstance() { return new T; }

class MusicItemsDB
{
private:

	items_class_handlers items_class_handlers_;
	dummy_class_handlers dummy_class_handlers_;

	std::vector <InstrumentCategory> categories_;

	void addToStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, std::vector <std::string>& item_data);
	void stockNewItem(std::vector <std::string>& item_data);

	std::vector<InstrumentCategory>::iterator getCategoryIterator(std::string category_name);

public:

	MusicItemsDB();
	~MusicItemsDB();

	std::vector<InstrumentCategory>::iterator createCategory(std::string category_name);
	void deleteCategory(std::vector<InstrumentCategory>::iterator category_to_delete);
	void eraseDatabase();

	void requestItemAdding(std::vector <std::string>& item_data);
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> findItem(std::string model_name);
	std::pair <std::vector<std::reference_wrapper<Instrument>>::iterator, bool> findItem(std::string company_name,
		std::string model_name);
	std::pair <std::vector<InstrumentCategory>::iterator, bool> findCategory(std::string category_name);

	size_t getCategoriesNumber();
	Instrument* getDummyInstance(const std::string& instrument_name);
	Instrument* getInstance(const std::vector<std::string>& item_data);
};