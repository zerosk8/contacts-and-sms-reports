#ifndef _TELEPHONE_NUMBER_H_
#define _TELEPHONE_NUMBER_H_
#include <string>

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

class TelephoneNumber
{
    public:
        TelephoneNumber();
        TelephoneNumber(const std::string & number, const std::string & countryDialCode = std::string());
        std::string GetNumber() const;
        std::string GetCountryDialCode() const;
        bool ContainsCountryDialCode() const;
        TelephoneNumber & operator=(const TelephoneNumber & telephoneNumber);
        ~TelephoneNumber();
    private:
        std::string number;
        std::string countryDialCode;
        bool containsCountryDialCode;
};

#endif