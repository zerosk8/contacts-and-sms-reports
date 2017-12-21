#include "telephone_number.h"

TelephoneNumber::TelephoneNumber()
{
    this->number = std::string();
    this->countryDialCode = std::string();
    this->containsCountryDialCode = false;
}

TelephoneNumber::TelephoneNumber(const std::string & number, const std::string & countryDialCode)
{
    this->number = number;
    this->countryDialCode = countryDialCode;
    (!countryDialCode.empty())?this->containsCountryDialCode = true:this->containsCountryDialCode = false;
}

std::string TelephoneNumber::GetNumber()
{
    return number;
}

std::string TelephoneNumber::GetCountryDialCode()
{
    return countryDialCode;
}

bool TelephoneNumber::ContainsCountryDialCode()
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
