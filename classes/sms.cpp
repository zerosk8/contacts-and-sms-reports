#include "sms.h"

Sms::Sms(){}

Sms::Sms(const TelephoneNumber & phoneNumber, const std::string & contactName, const std::string & dateAndTime, const SmsType & type, const std::string & text)
{
    this->phoneNumber = phoneNumber;
    this->contactName = contactName;
    this->dateAndTime = dateAndTime;
    this->type = type;
    this->text = text;
}

void Sms::SetTelephoneNumber(const TelephoneNumber & phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Sms::SetContactName(const std::string & contactName)
{
    this->contactName = contactName;
}

void Sms::SetDateAndTime(const std::string & dateAndTime)
{
    this->dateAndTime = dateAndTime;
}

void Sms::SetType(const SmsType & type)
{
    this->type = type;
}

void Sms::SetText(const std::string & text)
{
    this->text = text;
}

TelephoneNumber Sms::GetTelephoneNumber()
{
    return phoneNumber;
}

std::string Sms::GetContactName()
{
    return contactName;
}

std::string Sms::GetDateAndTime()
{
    return dateAndTime;
}

SmsType Sms::GetType()
{
    return type;
}

std::string Sms::GetText()
{
    return text;
}

Sms & Sms::operator=(const Sms & sms)
{
    if(this != &sms)
    {
        this->phoneNumber = sms.phoneNumber;
        this->contactName = sms.contactName;
        this->dateAndTime = sms.dateAndTime;
        this->type = sms.type;
        this->text = sms.text;
    }
    return * this;
}

Sms::~Sms(){}
