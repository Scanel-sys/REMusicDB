#pragma once


#include <string>
#include <vector>
#include <sstream>


class Instrument
{
private:
	std::string company_name_;
	std::string model_name_;
	uint64_t price;
	uint64_t count;

public:
	Instrument(std::vector <std::string> data);

	std::string getCompanyName();
	std::string getModelName();
	std::uint64_t getModelPrice();
	std::uint64_t getModelCount();

	void setCompanyName(std::string company_name);
	void setModelName(std::string model_name);
	void setModelPrice(uint64_t price);
	void setModelCount(uint64_t count);

	virtual void showInfo() = 0;
};


class Guitar : public Instrument 
{
private:
	std::string company_name_;
	std::string model_name_;
	uint64_t price;
	uint64_t count;

public:
	Guitar(std::vector <std::string> data);

	void showInfo() override;
};

class Keyboard : Instrument
{
private:
	std::string company_name_;
	std::string model_name_;
	uint64_t price;
	uint64_t count;

public:
	Keyboard(std::vector <std::string> data);

	void showInfo() override;
};

class Bass : Instrument
{
private:
	std::string company_name_;
	std::string model_name_;
	uint64_t price;
	uint64_t count;

public:
	Bass(std::vector <std::string> data);

	void showInfo() override;
};