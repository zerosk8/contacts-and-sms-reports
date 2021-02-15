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
    if(!this->isNumber(number))
    {
        throw std::invalid_argument("Telephone number is not a numeric string");
    }
    if(!countryDialCode.empty() && !this->isNumber(countryDialCode))
    {
        throw std::invalid_argument("Country dial code is not a numeric string");
    }
    this->number = number;
    this->countryDialCode = countryDialCode;
    (!countryDialCode.empty())?this->containsCountryDialCode = true:this->containsCountryDialCode = false;
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

TelephoneNumber::~TelephoneNumber(){};

bool TelephoneNumber::isNumber(const std::string & value) const
{
    return value.find_first_not_of("0123456789") == std::string::npos;
}
