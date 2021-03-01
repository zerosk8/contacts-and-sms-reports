#ifndef _TELEPHONE_NUMBER_HPP_
#define _TELEPHONE_NUMBER_HPP_
#include <string>
#include <stdexcept>

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

class TelephoneNumber
{
    public:
        const std::string COUNTRY_DIAL_CODE_START = "+";

        TelephoneNumber();
        TelephoneNumber(const std::string & number, const std::string & countryDialCode = std::string());
        std::string GetNumber() const;
        std::string GetCountryDialCode() const;
        bool ContainsCountryDialCode() const;
        TelephoneNumber & operator=(const TelephoneNumber & telephoneNumber);
        bool operator==(const TelephoneNumber & telephoneNumber) const;
        bool operator!=(const TelephoneNumber & telephoneNumber) const;
        ~TelephoneNumber();
    private:
        std::string number;
        std::string countryDialCode;
        bool containsCountryDialCode;
        bool isNumber(const std::string & value) const;
};

#endif
