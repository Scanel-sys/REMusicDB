#include "DBase.h"

#include <iostream>


int main()
{
	std::vector<std::string> item_init_data;
	item_init_data.push_back("ibanez");
	item_init_data.push_back("zalupa 1");
	item_init_data.push_back("330");
	item_init_data.push_back("2");

	Bass item{item_init_data};

}