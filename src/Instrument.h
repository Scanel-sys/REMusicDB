#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include <cctype>


class Instrument
{
protected:
	std::string company_name_;
	std::string model_name_;
	unsigned long price;
	unsigned long count;

	Instrument(std::vector <std::string>& data);

	static bool isLegalUInt(std::string const& input);
	static std::string toLowerCase(std::string &data);

	enum class neck { BOLT_ON = 0, SET_NECK, NECK_TROUGH };
	enum class logic { NO = 0, YES };
	enum class comparing { DIFFERENT = 0, SAME, SIMILAR };
	enum class handOrientation { LH = 0, RH };
	enum class bassType { PRECISION = 0, JAZZ, HALF_ACOUSTIC, NO_FRETS };

public:
	std::string getCompanyName();
	std::string getModelName();
	unsigned long getModelPrice();
	unsigned long getModelCount();

	void setCompanyName(std::string company_name);
	void setModelName(std::string model_name);
	void setModelPrice(unsigned long price);
	void setModelCount(unsigned long count);

	virtual std::vector <std::string> prepareItemInfo() = 0;
	static bool isValidData(std::vector <std::string> &data_to_validate);
};



class Guitar : public Instrument 
{
private:
	unsigned int strings_;
	enum neck neck_;
	unsigned int frets_;
	enum handOrientation hand_;

public:
	Guitar(std::vector <std::string>& data);

	std::vector <std::string> prepareItemInfo() override;
	static bool isValidData(std::vector <std::string>& data_to_validate);
};



class Keyboard : public Instrument
{
private:
	unsigned int keys_;
	bool usb_;
	bool modWheel_;
	bool imitHamMech_;
	unsigned int analOutput_;

public:
	Keyboard(std::vector <std::string> &data);

	std::vector <std::string> prepareItemInfo() override;
	static bool isValidData(std::vector <std::string>& data_to_validate);
};



class Bass : public Instrument
{
private:
	unsigned int strings_;
	enum neck neck_;
	unsigned int frets_;
	enum handOrientation hand_;
	enum bassType typeOfBass_;

public:
	Bass(std::vector <std::string> &data);

	std::vector <std::string> prepareItemInfo() override;
	static bool isValidData(std::vector <std::string>& data_to_validate);
};