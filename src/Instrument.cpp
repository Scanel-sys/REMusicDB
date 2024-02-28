#include "Instrument.h"

// public

Instrument::Instrument()
{
	this->setCompanyName("dummy");
	this->setModelName("dummy");
	this->setModelCount(0);
	this->setModelPrice(0);
}

Instrument::Instrument(std::vector <std::string> &data)
{
	this->setCompanyName(data[COMPANY_NAME_IDX]);
	this->setModelName(data[MODEL_NAME_IDX]);
	this->setModelCount(std::stoul(data[PRICE_IDX]));
	this->setModelPrice(std::stoul(data[COUNT_IDX]));
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
	this->price_ = price;
}

void Instrument::setModelCount(unsigned long count)
{
	this->count_ = count;
}

void Instrument::addToStock(unsigned long items_count)
{
	this->count_ += items_count;
}

void Instrument::takeFromStock(unsigned long take_from_stock)
{
	if (this->count_ >= take_from_stock)
		this->count_ -= take_from_stock;
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
	return this->price_;
}

unsigned long Instrument::getModelCount()
{
	return this->count_;
}


// derived class

Guitar::Guitar() : Instrument()
{
	this->setStringsNum("0");
	this->setNeckType("dummy");
	this->setFretsNum("0");
	this->setHandOriantation("lh");
}

Guitar::Guitar(std::vector <std::string> &data) : Instrument(data)
{
	this->setStringsNum(data[STRINGS_NUMBER_IDX]);
	this->setNeckType(data[NECK_TYPE_IDX]);
	this->setFretsNum(data[FRETS_NUMBER_IDX]);
	this->setHandOriantation(data[HAND_ORIANTATION_IDX]);
}

void Guitar::setStringsNum(std::string data)
{
	this->strings_ = std::stoul(data);
}

void Guitar::setFretsNum(std::string data)
{
	this->frets_ = std::stoul(data);
}

void Guitar::setNeckType(std::string data)
{
	if (data == "bolt on")
		this->neck_ = neck::BOLT_ON;
	else if (data == "set neck")
		this->neck_ = neck::SET_NECK;
	else
		this->neck_ = neck::NECK_TROUGH;
}

void Guitar::setHandOriantation(std::string data)
{
	if (data == "rh" || data == "right hand")
		this->hand_ = handOrientation::RH;
	else
		this->hand_ = handOrientation::LH;
}

std::vector <std::string> Guitar::prepareItemInfo()
{
	std::vector <std::string> output = this->takeRecordFieldsStrings();
	output[COMPANY_NAME_IDX] += this->company_name_;
	output[MODEL_NAME_IDX] += this->model_name_;
	output[PRICE_IDX] += std::to_string(this->price_);
	output[COUNT_IDX] += std::to_string(this->count_);
	output[STRINGS_NUMBER_IDX] += std::to_string(this->strings_);

	if (this->neck_ == neck::BOLT_ON)
		output[NECK_TYPE_IDX] += "bolt on";
	else if (this->neck_ == neck::SET_NECK)
		output[NECK_TYPE_IDX] += "set neck";
	else
		output[NECK_TYPE_IDX] += "neck through";

	output[FRETS_NUMBER_IDX] += std::to_string(this->frets_);

	if (this->hand_ == handOrientation::LH)
		output[HAND_ORIANTATION_IDX] += "lh";
	else
		output[HAND_ORIANTATION_IDX] += "rh";

	return output;
}

std::vector<std::string> Guitar::takeRecordFieldsStrings()
{
	std::vector<std::string> output;
	output.push_back("guitar");
	output.push_back("company name: ");
	output.push_back("model name: ");
	output.push_back("price: ");
	output.push_back("count: ");
	output.push_back("strings number: ");
	output.push_back("neck type: ");
	output.push_back("frets number: ");
	output.push_back("hand oriantation: ");
	return output;
}

bool Guitar::isValidData(std::vector<std::string>& data_to_validate)
{
	if (data_to_validate.size() != GUITAR_DATA_SIZE)
		return false;

	if (!isLegalUInt(data_to_validate[PRICE_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[COUNT_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[STRINGS_NUMBER_IDX]))
		return false;

	data_to_validate[NECK_TYPE_IDX] = toLowerCase(data_to_validate[NECK_TYPE_IDX]);
	if (data_to_validate[NECK_TYPE_IDX] != "bolt on" &&
		data_to_validate[NECK_TYPE_IDX] != "set neck" &&
		data_to_validate[NECK_TYPE_IDX] != "neck through")
		return false;

	if (!isLegalUInt(data_to_validate[FRETS_NUMBER_IDX]))
		return false;

	data_to_validate[HAND_ORIANTATION_IDX] = toLowerCase(data_to_validate[HAND_ORIANTATION_IDX]);
	if (data_to_validate[HAND_ORIANTATION_IDX] != "rh" &&
		data_to_validate[HAND_ORIANTATION_IDX] != "lh")
		return false;

	return true;
}



Bass::Bass() : Instrument()
{
	this->setStringsNum("0");
	this->setNeckType("dummy");
	this->setFretsNum("0");
	this->setHandOriantation("dummy");
	this->setBassType("dummy");
}

Bass::Bass(std::vector <std::string> &data) : Instrument(data)
{
	this->setStringsNum(data[STRINGS_NUMBER_IDX]);
	this->setNeckType(data[NECK_TYPE_IDX]);
	this->setFretsNum(data[FRETS_NUMBER_IDX]);
	this->setHandOriantation(data[HAND_ORIANTATION_IDX]);
	this->setBassType(data[BASS_TYPE_IDX]);
}

void Bass::setStringsNum(std::string data)
{
	this->strings_ = std::stoul(data);
}

void Bass::setFretsNum(std::string data)
{
	this->frets_ = std::stoul(data);
}

void Bass::setNeckType(std::string data)
{
	if (data == "bolt on")
		this->neck_ = neck::BOLT_ON;
	else if (data == "set neck")
		this->neck_ = neck::SET_NECK;
	else
		this->neck_ = neck::NECK_TROUGH;
}

void Bass::setHandOriantation(std::string data)
{
	if (data == "rh" || data == "right hand")
		this->hand_ = handOrientation::RH;
	else
		this->hand_ = handOrientation::LH;
}

void Bass::setBassType(std::string data)
{
	if (data == "precision")
		this->typeOfBass_ = bassType::PRECISION;
	else if (data == "jazz")
		this->typeOfBass_ = bassType::JAZZ;
	else if (data == "half acoustic")
		this->typeOfBass_ = bassType::HALF_ACOUSTIC;
	else
		this->typeOfBass_ = bassType::NO_FRETS;
}

std::vector <std::string> Bass::prepareItemInfo()
{
	std::vector <std::string> output = this->takeRecordFieldsStrings();
	output[COMPANY_NAME_IDX] += this->company_name_;
	output[MODEL_NAME_IDX] += this->model_name_;
	output[PRICE_IDX] += std::to_string(this->price_);
	output[COUNT_IDX] += std::to_string(this->count_);
	output[STRINGS_NUMBER_IDX] += std::to_string(this->strings_);
	
	if(this->neck_ == neck::BOLT_ON)
		output[NECK_TYPE_IDX] += "bolt on";
	else if(this->neck_ == neck::SET_NECK)
		output[NECK_TYPE_IDX] += "set neck";
	else
		output[NECK_TYPE_IDX] += "neck through";

	output[FRETS_NUMBER_IDX] += std::to_string(this->frets_);

	if (this->hand_ == handOrientation::LH)
		output[HAND_ORIANTATION_IDX] += "lh";
	else
		output[HAND_ORIANTATION_IDX] += "rh";

	if (this->typeOfBass_ == bassType::PRECISION)
		output[BASS_TYPE_IDX] += "precision";
	else if(this->typeOfBass_ == bassType::JAZZ)
		output[BASS_TYPE_IDX] += "jazz";
	else
		output[BASS_TYPE_IDX] += "half acoustic";

	return output;
}

std::vector<std::string> Bass::takeRecordFieldsStrings()
{
	std::vector<std::string> output;
	output.push_back("bass guitar");
	output.push_back("company name: ");
	output.push_back("model name: ");
	output.push_back("price: ");
	output.push_back("count: ");
	output.push_back("strings number: ");
	output.push_back("neck type: ");
	output.push_back("frets number: ");
	output.push_back("hand oriantation: ");
	output.push_back("bass type: ");
	return output;
}

bool Bass::isValidData(std::vector<std::string>& data_to_validate)
{
	if (data_to_validate.size() != BASS_DATA_SIZE)
		return false;

	if (!isLegalUInt(data_to_validate[PRICE_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[COUNT_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[STRINGS_NUMBER_IDX]))
		return false;

	data_to_validate[NECK_TYPE_IDX] = toLowerCase(data_to_validate[NECK_TYPE_IDX]);
	if (data_to_validate[NECK_TYPE_IDX] != "bolt on" &&
		data_to_validate[NECK_TYPE_IDX] != "set neck" &&
		data_to_validate[NECK_TYPE_IDX] != "neck through")
		return false;

	if (!isLegalUInt(data_to_validate[FRETS_NUMBER_IDX]))
		return false;

	data_to_validate[HAND_ORIANTATION_IDX] = toLowerCase(data_to_validate[HAND_ORIANTATION_IDX]);
	if (data_to_validate[HAND_ORIANTATION_IDX] != "rh" &&
		data_to_validate[HAND_ORIANTATION_IDX] != "lh")
		return false;

	data_to_validate[BASS_TYPE_IDX] = toLowerCase(data_to_validate[BASS_TYPE_IDX]);
	if (data_to_validate[BASS_TYPE_IDX] != "precision" &&
		data_to_validate[BASS_TYPE_IDX] != "jazz" &&
		data_to_validate[BASS_TYPE_IDX] != "half acoustic")
		return false;

	return true;
}


Keyboard::Keyboard() : Instrument()
{
	this->setKeysNum("0");
	this->setUsbInfo("dummy");
	this->setModWheelInfo("dummy");
	this->setImitHammerMechInfo("dummy");
	this->setAnalOutputNum("0");
}

Keyboard::Keyboard(std::vector <std::string> &data) : Instrument(data)
{
	this->setKeysNum(data[KEYS_NUMBER_IDX]);
	this->setUsbInfo(data[USB_INFO_IDX]);
	this->setModWheelInfo(data[MODUL_WHEEL_INFO_IDX]);
	this->setImitHammerMechInfo(data[HAMMER_IMITATION_IDX]);
	this->setAnalOutputNum(data[ANALOG_OUT_COUNT_IDX]);
}

void Keyboard::setKeysNum(std::string data)
{
	this->keys_ = std::stoul(data);
}

void Keyboard::setUsbInfo(std::string data)
{
	this->usb_ = data == "yes";
}

void Keyboard::setModWheelInfo(std::string data)
{
	this->modWheel_ = data == "yes";
}

void Keyboard::setImitHammerMechInfo(std::string data)
{
	this->imitHamMech_ = data == "yes";
}

void Keyboard::setAnalOutputNum(std::string data)
{
	this->analOutput_ = std::stoul(data);
}

std::vector <std::string> Keyboard::prepareItemInfo()
{
	std::vector <std::string> output = this->takeRecordFieldsStrings();
	output[COMPANY_NAME_IDX] += this->company_name_;
	output[MODEL_NAME_IDX] += this->model_name_;
	output[PRICE_IDX] += std::to_string(this->price_);
	output[COUNT_IDX] += std::to_string(this->count_);

	output[KEYS_NUMBER_IDX] += std::to_string(this->keys_);
	
	if (this->usb_)
		output[USB_INFO_IDX] += "yes";
	else
		output[USB_INFO_IDX] += "no";

	if (this->modWheel_)
		output[MODUL_WHEEL_INFO_IDX] += "yes";
	else
		output[MODUL_WHEEL_INFO_IDX] += "no";

	if (this->imitHamMech_)
		output[HAMMER_IMITATION_IDX] += "yes";
	else
		output[HAMMER_IMITATION_IDX] += "no";

	output[ANALOG_OUT_COUNT_IDX] += std::to_string(this->analOutput_);
	
	return output;
}

std::vector<std::string> Keyboard::takeRecordFieldsStrings()
{
	std::vector<std::string> output;
	output.push_back("keyboard");
	output.push_back("company name: ");
	output.push_back("model name: ");
	output.push_back("price: ");
	output.push_back("count: ");
	output.push_back("keys number: ");
	output.push_back("has usb: ");
	output.push_back("has modwheel: ");
	output.push_back("has hammer imitation: ");
	output.push_back("analog output count: ");
	return output;
}

bool Keyboard::isValidData(std::vector<std::string>& data_to_validate)
{
	if (data_to_validate.size() != KEYBOARD_DATA_SIZE)
		return false;

	if (!isLegalUInt(data_to_validate[PRICE_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[COUNT_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[KEYS_NUMBER_IDX]))
		return false;

	if (!isLegalUInt(data_to_validate[ANALOG_OUT_COUNT_IDX]))
		return false;

	data_to_validate[USB_INFO_IDX] = toLowerCase(data_to_validate[USB_INFO_IDX]);
	if (data_to_validate[USB_INFO_IDX] != "yes" ||
		data_to_validate[USB_INFO_IDX] != "no" ||
		data_to_validate[USB_INFO_IDX] != "n" ||
		data_to_validate[USB_INFO_IDX] != "y")
		return false;
	
	data_to_validate[MODUL_WHEEL_INFO_IDX] = toLowerCase(data_to_validate[MODUL_WHEEL_INFO_IDX]);
	if (data_to_validate[MODUL_WHEEL_INFO_IDX] != "yes" ||
		data_to_validate[MODUL_WHEEL_INFO_IDX] != "no" ||
		data_to_validate[MODUL_WHEEL_INFO_IDX] != "n" ||
		data_to_validate[MODUL_WHEEL_INFO_IDX] != "y")
		return false;

	data_to_validate[HAMMER_IMITATION_IDX] = toLowerCase(data_to_validate[HAMMER_IMITATION_IDX]);
	if (data_to_validate[HAMMER_IMITATION_IDX] != "yes" ||
		data_to_validate[HAMMER_IMITATION_IDX] != "no" ||
		data_to_validate[HAMMER_IMITATION_IDX] != "n" ||
		data_to_validate[HAMMER_IMITATION_IDX] != "y")
		return false;

	return true;
}
