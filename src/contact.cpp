#include "contact.hpp"

Contact::Contact(){}

Contact::Contact(const std::string & name, const std::vector<TelephoneNumber> & listOfTelephoneNumbers,
    const std::vector<std::string> & listOfEmailAddresses, const std::vector<Sms> & listOfSms)
{
    if(name.empty() || listOfTelephoneNumbers.empty())
    {
        throw std::invalid_argument("Empty contact name or list of telephone numbers");
    }
    this->name = name;
    this->listOfTelephoneNumbers = listOfTelephoneNumbers;
    this->listOfEmailAddresses = listOfEmailAddresses;
    this->listOfSms = listOfSms;
}

void Contact::SetName(const std::string & name)
{
    this->name = name;
}

void Contact::SetListOfTelephoneNumbers(const std::vector<TelephoneNumber> & listOfTelephoneNumbers)
{
    this->listOfTelephoneNumbers = listOfTelephoneNumbers;
}

void Contact::SetListOfEmailAddresses(const std::vector<std::string> & listOfEmailAddresses)
{
    this->listOfEmailAddresses = listOfEmailAddresses;
}

void Contact::SetListOfSms(const std::vector<Sms> & listOfSms)
{
    this->listOfSms = listOfSms;
}

std::string Contact::GetName() const
{
    return name;
}

std::vector<TelephoneNumber> Contact::GetListOfTelephoneNumbers() const
{
    return listOfTelephoneNumbers;
}

std::vector<std::string> Contact::GetListOfEmailAddresses() const
{
    return listOfEmailAddresses;
}

std::vector<Sms> Contact::GetListOfSms() const
{
    return listOfSms;
}

void Contact::AddTelephoneNumber(const TelephoneNumber & phoneNumber)
{
    listOfTelephoneNumbers.push_back(phoneNumber);
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
        this->listOfTelephoneNumbers = contact.listOfTelephoneNumbers;
        this->listOfEmailAddresses = contact.listOfEmailAddresses;
        this->listOfSms = contact.listOfSms;
    }
    return * this;
}

Contact::~Contact(){}

