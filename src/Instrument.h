#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#define GUITAR_DATA_SIZE		(9)
#define BASS_DATA_SIZE			(10)
#define KEYBOARD_DATA_SIZE		(10)


#define COMPANY_NAME_IDX		(1)
#define MODEL_NAME_IDX			(2)
#define PRICE_IDX				(3)
#define COUNT_IDX				(4)

#define STRINGS_NUMBER_IDX		(5)
#define NECK_TYPE_IDX			(6)
#define FRETS_NUMBER_IDX		(7)
#define HAND_ORIANTATION_IDX	(8)

#define BASS_TYPE_IDX			(9)

#define KEYS_NUMBER_IDX			(5)
#define USB_INFO_IDX			(6)
#define	MODUL_WHEEL_INFO_IDX	(7)
#define HAMMER_IMITATION_IDX	(8)
#define ANALOG_OUT_COUNT_IDX	(9)


class Instrument
{
protected:
	std::string company_name_;
	std::string model_name_;
	unsigned long price_;
	unsigned long count_;

	Instrument();
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

	void addToStock(unsigned long items_count);

	virtual std::vector <std::string> prepareItemInfo() = 0;
	virtual std::vector <std::string> takeRecordFieldsStrings() = 0;
	virtual bool isValidData(std::vector <std::string> &data_to_validate) = 0;
};


class Guitar : public Instrument 
{
private:
	unsigned int strings_;
	enum neck neck_;
	unsigned int frets_;
	enum handOrientation hand_;

public:
	Guitar();
	Guitar(std::vector <std::string>& data);

	void setStringsNum(std::string data);
	void setFretsNum(std::string data);
	void setNeckType(std::string data);
	void setHandOriantation(std::string data);

	std::vector <std::string> prepareItemInfo() override;
	std::vector <std::string> takeRecordFieldsStrings() override;
	bool isValidData(std::vector <std::string>& data_to_validate) override;
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
	Bass();
	Bass(std::vector <std::string> &data);

	void setStringsNum(std::string data);
	void setFretsNum(std::string data);
	void setNeckType(std::string data);
	void setHandOriantation(std::string data);
	void setBassType(std::string data);

	std::vector <std::string> prepareItemInfo() override;
	std::vector <std::string> takeRecordFieldsStrings() override;
	bool isValidData(std::vector <std::string>& data_to_validate) override;
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
	Keyboard();
	Keyboard(std::vector <std::string>& data);

	void setKeysNum(std::string data);
	void setUsbInfo(std::string data);
	void setModWheelInfo(std::string data);
	void setImitHammerMechInfo(std::string data);
	void setAnalOutputNum(std::string data);

	std::vector <std::string> prepareItemInfo() override;
	std::vector <std::string> takeRecordFieldsStrings() override;
	bool isValidData(std::vector <std::string>& data_to_validate) override;
};