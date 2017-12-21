#ifndef _SMS_H_
#define _SMS_H_
#include <string>
#include "telephone_number.h"

enum SmsType {incoming, outgoing, unknown};

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

class Sms
{
    public:
        Sms();
        Sms(const TelephoneNumber & phoneNumber, const std::string & contactName, const std::string & dateAndTime, const SmsType & type, const std::string & text);
        void SetTelephoneNumber(const TelephoneNumber & phoneNumber);
        void SetContactName(const std::string & contactName);
        void SetDateAndTime(const std::string & dateAndTime);
        void SetType(const SmsType & type);
        void SetText(const std::string & text);
        TelephoneNumber GetTelephoneNumber();
        std::string GetContactName();
        std::string GetDateAndTime();
        SmsType GetType();
        std::string GetText();
        Sms & operator=(const Sms & sms);
        ~Sms();
    private:
        TelephoneNumber phoneNumber;
        std::string contactName;
        std::string dateAndTime;
        SmsType type;
        std::string text;
};

#endif
