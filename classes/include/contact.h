#ifndef _CONTACT_H_
#define _CONTACT_H_
#include <string>
#include <vector>
#include "telephone_number.h"
#include "sms.h"

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

class Contact
{
    public:
        Contact();
        Contact(const std::string & name, const std::vector<TelephoneNumber> & phoneNumbers, 
        const std::vector<std::string> & emails, const std::vector<Sms> & listOfSms = std::vector<Sms>());
        void SetName(const std::string & name);
        void SetTelephoneNumbers(const std::vector<TelephoneNumber> & phoneNumbers);
        void SetEmails(const std::vector<std::string> & emails);
        void SetListOfSms(const std::vector<Sms> & listOfSms);
        std::string GetName() const;
        std::vector<TelephoneNumber> GetTelephoneNumbers() const;
        std::vector<std::string> GetEmails() const;
        std::vector<Sms> GetListOfSms() const;
        void AddTelephoneNumber(const TelephoneNumber & phoneNumber);
        void AddSms(const Sms & sms);
        Contact & operator=(const Contact & contact);
        ~Contact();
    private:
        std::string name;
        std::vector<TelephoneNumber> phoneNumbers;
        std::vector<std::string> emails;
        std::vector<Sms> listOfSms;
};

#endif
