#include "telephone_number.hpp"

TelephoneNumber::TelephoneNumber()
{
    this->number = std::string();
    this->countryDialCode = std::string();
    this->containsCountryDialCode = false;
}

TelephoneNumber::TelephoneNumber(const std::string & number, const std::string & countryDialCode)
{
    if(number.empty())
    {
        throw std::invalid_argument("Empty telephone number");
    }
    if(!isNumber(number))
    {
        throw std::invalid_argument("Telephone number is not a numeric string");
    }
    if(!countryDialCode.empty()
        && (COUNTRY_DIAL_CODE_START.compare(countryDialCode.substr(0,COUNTRY_DIAL_CODE_START.length())) != 0)
        && !isNumber(countryDialCode.substr(COUNTRY_DIAL_CODE_START.length())))
    {
        throw std::invalid_argument("Country dial code is not a formatted numeric string ( e.g.: " + COUNTRY_DIAL_CODE_START + "12 )");
    }
    this->number = number;
    this->countryDialCode = countryDialCode;
    this->containsCountryDialCode = (!countryDialCode.empty())?true:false;
}

std::string TelephoneNumber::GetNumber() const
{
    return number;
}

std::string TelephoneNumber::GetCountryDialCode() const
{
    return countryDialCode;
}

bool TelephoneNumber::ContainsCountryDialCode() const
{
    return containsCountryDialCode;
}

TelephoneNumber & TelephoneNumber::operator=(const TelephoneNumber & telephoneNumber)
{
    if(this != &telephoneNumber)
    {
        this->number = telephoneNumber.number;
        this->countryDialCode = telephoneNumber.countryDialCode;
        this->containsCountryDialCode = telephoneNumber.containsCountryDialCode;
    }
    return * this;
}

bool TelephoneNumber::operator==(const TelephoneNumber & telephoneNumber) const
{
    return (this->number == telephoneNumber.number)
        && (this->countryDialCode == telephoneNumber.countryDialCode);
}

bool TelephoneNumber::operator!=(const TelephoneNumber & telephoneNumber) const
{
    return (this->number != telephoneNumber.number)
        || (this->countryDialCode != telephoneNumber.countryDialCode);
}

TelephoneNumber::~TelephoneNumber(){};

bool TelephoneNumber::isNumber(const std::string & value) const
{
    return value.find_first_not_of("0123456789") == std::string::npos;
}
