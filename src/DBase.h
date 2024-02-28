#pragma once

#include "InstrumentCategory.h"

#include <vector>
#include <string>
#include <map>

typedef std::map < std::string, Instrument* (*)(std::vector<std::string>) > items_class_handlers;
typedef std::map < std::string, Instrument* (*)() > dummy_class_handlers;

template<typename T> Instrument* createInstance(std::vector<std::string> arg) { return new T(arg); }
template<typename T> Instrument* createDummyInstance() { return new T; }

class MusicItemsDB
{
private:

	std::vector <InstrumentCategory>::iterator act_category_;
	std::vector <std::reference_wrapper<Instrument>>::iterator act_category_item_;

	items_class_handlers items_class_handlers_;
	dummy_class_handlers dummy_class_handlers_;

	std::vector <InstrumentCategory> categories_;

	void addToStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, std::vector <std::string>& item_data);
	void addToStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, unsigned long add_to_stock_count);
	void takeFromStock(std::vector<std::reference_wrapper<Instrument>>::iterator item_iter, unsigned long take_from_stock_count);
	void stockNewItem(std::vector <std::string>& item_data);

	std::vector<InstrumentCategory>::iterator getCategoryIterator(std::string category_name);
	void setIterators(std::vector <InstrumentCategory>::iterator category_iterator, std::vector <std::reference_wrapper<Instrument>>::iterator item_iterator);

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
	
	std::vector <std::string> getScrollingItemOutputData();
	std::vector<std::vector<std::string>> prepareItemsForFileWrite();

	static bool isLegalUInt(std::string const& input);

	bool empty();
	bool ifScrollingCategoryEmpty();

	bool ifFirstCategory();
	bool ifLastCategory();
	bool ifFirstItem();
	bool ifLastItem();

	void nextCategory();
	void prevCategory();
	void nextItem();
	void prevItem();

	void stockToScrollingItem(unsigned long count);
	void takeScrollingItemFromStock(unsigned long count);
};