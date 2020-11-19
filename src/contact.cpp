#include "contact.h"

Contact::Contact(){}

Contact::Contact(const std::string & name, const std::vector<TelephoneNumber> & phoneNumbers, const std::vector<std::string> & emails, 
const std::vector<Sms> & listOfSms)
{
    this->name = name;
    this->phoneNumbers = phoneNumbers;
    this->emails = emails;
    this->listOfSms = listOfSms;
}

void Contact::SetName(const std::string & name)
{
    this->name = name;
}

void Contact::SetTelephoneNumbers(const std::vector<TelephoneNumber> & phoneNumbers)
{
    this->phoneNumbers = phoneNumbers;
}

void Contact::SetEmails(const std::vector<std::string> & emails)
{
    this->emails = emails;
}

void Contact::SetListOfSms(const std::vector<Sms> & listOfSms)
{
    this->listOfSms = listOfSms;
}

std::string Contact::GetName() const
{
    return name;
}

std::vector<TelephoneNumber> Contact::GetTelephoneNumbers() const
{
    return phoneNumbers;
}

std::vector<std::string> Contact::GetEmails() const
{
    return emails;
}

std::vector<Sms> Contact::GetListOfSms() const
{
    return listOfSms;
}

void Contact::AddTelephoneNumber(const TelephoneNumber & phoneNumber)
{
    phoneNumbers.push_back(phoneNumber);
}

void Contact::AddSms(const Sms & sms)
{
    listOfSms.push_back(sms);
}

Contact & Contact::operator=(const Contact & contact)
{
    if(this != &contact)
    {
        this->name = contact.name;
        this->phoneNumbers = contact.phoneNumbers;
        this->emails = contact.emails;
        this->listOfSms = contact.listOfSms;
    }
    return * this;
}

Contact::~Contact(){}

