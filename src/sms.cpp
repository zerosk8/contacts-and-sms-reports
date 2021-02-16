#include "sms.hpp"

Sms::Sms()
{
    this->type = SmsType::unknown;
}

Sms::Sms(const TelephoneNumber & phoneNumber, const std::string & contactName, const std::string & dateAndTime, const SmsType & type, const std::string & text)
{
    if(phoneNumber.GetNumber().empty() || contactName.empty() || dateAndTime.empty() || text.empty())
    {
        throw std::invalid_argument("One or more paremeters are empty");
    }
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

TelephoneNumber Sms::GetTelephoneNumber() const
{
    return phoneNumber;
}

std::string Sms::GetContactName() const
{
    return contactName;
}

std::string Sms::GetDateAndTime() const
{
    return dateAndTime;
}

SmsType Sms::GetType() const
{
    return type;
}

std::string Sms::GetText() const
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

bool Sms::operator==(const Sms & sms) const
{
    return this->phoneNumber == sms.phoneNumber && this->contactName == sms.contactName
        && this->dateAndTime == sms.dateAndTime && this->type == sms.type
        && this->text == sms.text;
}

bool Sms::operator!=(const Sms & sms) const
{
    return this->phoneNumber != sms.phoneNumber || this->contactName != sms.contactName
        || this->dateAndTime != sms.dateAndTime || this->type != sms.type
        || this->text != sms.text;
}

Sms::~Sms(){}
