#include "Instrument.h"

// public

Instrument::Instrument(std::vector <std::string> &data)
{
	this->setCompanyName(data[0]);
	this->setModelName(data[1]);
	this->setModelCount(std::stoul(data[2]));
	this->setModelPrice(std::stoul(data[3]));
}

bool Instrument::isLegalUInt(std::string const& input)
{
	bool result = true;

	for (uint64_t i = 0; i < input.size() && result; i++)
		result = isdigit(input[i]);

	return result;
}

std::string Instrument::toLowerCase(std::string& data)
{
	std::string output = data;

	std::transform(output.begin(), output.end(), output.begin(),
		[](unsigned char c) { return std::tolower(c); });

	return output;
}

void Instrument::setCompanyName(std::string company_name)
{
	this->company_name_ = company_name;
}

void Instrument::setModelName(std::string model_name)
{
	this->model_name_ = model_name;
}

void Instrument::setModelPrice(unsigned long price)
{
	this->price = price;
}

void Instrument::setModelCount(unsigned long count)
{
	this->count = count;
}

bool Instrument::isValidData(std::vector<std::string> &data_to_validate)
{
	return false;
}


std::string Instrument::getCompanyName()
{
	return this->company_name_;
}

std::string Instrument::getModelName()
{
	return this->model_name_;
}

unsigned long Instrument::getModelPrice()
{
	return this->price;
}

unsigned long Instrument::getModelCount()
{
	return this->count;
}


// derived class

Guitar::Guitar(std::vector <std::string> &data) : Instrument(data)
{
	this->strings_ = std::stoul(data[4]);

	if (data[5] == "bolt on")
		this->neck_ = neck::BOLT_ON;
	else if (data[5] == "set neck")
		this->neck_ = neck::SET_NECK;
	else	
		this->neck_ = neck::NECK_TROUGH;

	this->frets_ = std::stoul(data[6]);

	if (data[7] == "rh" || data[7] == "right hand")
		this->hand_ = handOrientation::RH;
	else
		this->hand_ = handOrientation::LH;
}

std::vector <std::string> Guitar::prepareItemInfo()
{
	std::vector <std::string> output;
	return output;
}

bool Guitar::isValidData(std::vector<std::string>& data_to_validate)
{

	return false;
}



Bass::Bass(std::vector <std::string> &data) : Instrument(data)
{
	this->strings_ = std::stoul(data[4]);

	if (data[5] == "bolt on")
		this->neck_ = neck::BOLT_ON;
	else if (data[5] == "set neck")
		this->neck_ = neck::SET_NECK;
	else
		this->neck_ = neck::NECK_TROUGH;

	this->frets_ = std::stoul(data[6]);

	if (data[7] == "rh" || data[7] == "right hand")
		this->hand_ = handOrientation::RH;
	else
		this->hand_ = handOrientation::LH;

	if (data[8] == "precision")
		this->typeOfBass_ = bassType::PRECISION;
	if (data[8] == "jazz")
		this->typeOfBass_ = bassType::JAZZ;
	if (data[8] == "half acoustic")
		this->typeOfBass_ = bassType::HALF_ACOUSTIC;
	else
		this->typeOfBass_ = bassType::NO_FRETS;
}

std::vector <std::string> Bass::prepareItemInfo()
{
	std::vector <std::string> output;

	return output;
}

bool Bass::isValidData(std::vector<std::string>& data_to_validate)
{
	return false;
}



Keyboard::Keyboard(std::vector <std::string> &data) : Instrument(data)
{
	this->keys_ = std::stoul(data[4]);
	this->usb_ = data[5] == "yes";
	this->modWheel_ = data[6] == "yes";
	this->imitHamMech_ = data[7] == "yes";
	this->analOutput_ = std::stoul(data[8]);
}

std::vector <std::string> Keyboard::prepareItemInfo()
{
	std::vector <std::string> output;

	return output;
}

bool Keyboard::isValidData(std::vector<std::string>& data_to_validate)
{
	return false;
}
