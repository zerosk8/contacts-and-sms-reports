#ifndef _CONTACT_HPP_
#define _CONTACT_HPP_
#include <string>
#include <vector>
#include "telephone_number.hpp"
#include "sms.hpp"

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

class Contact
{
    public:
        Contact();
        Contact(const std::string & name, const std::vector<TelephoneNumber> & listOfTelephoneNumbers, 
            const std::vector<std::string> & listOfEmailAddresses = std::vector<std::string>(),
            const std::vector<Sms> & listOfSms = std::vector<Sms>());
        void SetName(const std::string & name);
        void SetListOfTelephoneNumbers(const std::vector<TelephoneNumber> & phoneNumbers);
        void SetListOfEmailAddresses(const std::vector<std::string> & emails);
        void SetListOfSms(const std::vector<Sms> & listOfSms);
        std::string GetName() const;
        std::vector<TelephoneNumber> GetListOfTelephoneNumbers() const;
        std::vector<std::string> GetListOfEmailAddresses() const;
        std::vector<Sms> GetListOfSms() const;
        void AddTelephoneNumber(const TelephoneNumber & phoneNumber);
        void AddSms(const Sms & sms);
        Contact & operator=(const Contact & contact);
        ~Contact();
    private:
        std::string name;
        std::vector<TelephoneNumber> listOfTelephoneNumbers;
        std::vector<std::string> listOfEmailAddresses;
        std::vector<Sms> listOfSms;
};

#endif
