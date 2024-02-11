#include "Instrument.h"


void Instrument::setCompanyName(std::string company_name)
{
	this->company_name_ = company_name;
}

void Instrument::setModelName(std::string model_name)
{
	this->model_name_ = model_name;
}

void Instrument::setModelPrice(uint64_t price)
{
	this->price = price;
}

void Instrument::setModelCount(uint64_t count)
{
	this->count = count;
}

Instrument::Instrument(std::vector <std::string> data)
{
	uint64_t price, count;

	this->setCompanyName(data[0]);
	this->setModelName(data[1]);

	std::stringstream iss(data[2]);
	iss >> count;
	this->setModelCount(count);

	std::stringstream iss(data[3]);
	iss >> price;
	this->setModelPrice(price);
}

std::string Instrument::getCompanyName()
{
	return this->company_name_;
}

std::string Instrument::getModelName()
{
	return this->model_name_;
}

std::uint64_t Instrument::getModelPrice()
{
	return this->price;
}

std::uint64_t Instrument::getModelCount()
{
	return this->count;
}


Guitar::Guitar(std::vector <std::string> data) : Instrument(data)
{

}

void Guitar::showInfo() 
{

}



Bass::Bass(std::vector <std::string> data) : Instrument(data)
{

}

void Bass::showInfo()
{

}

Keyboard::Keyboard(std::vector <std::string> data) : Instrument(data)
{

}

void Keyboard::showInfo()
{

}