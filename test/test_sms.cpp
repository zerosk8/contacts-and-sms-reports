#include "catch.hpp"
#include "sms.hpp"

std::string phoneNumber = "123456789", contactName = "Name",
    dateAndTime = "01/01/2021 00:00", text = "Hello, World";
SmsType type = SmsType::incoming;
Sms sms(phoneNumber,contactName,dateAndTime,type,text);
Sms emptySms;

TEST_CASE("Constructor with no parameters creates an empty Sms object","[Sms]")
{
    REQUIRE(emptySms.GetContactName().empty());
    REQUIRE(emptySms.GetDateAndTime().empty());
    REQUIRE(emptySms.GetType() == SmsType::unknown);
    REQUIRE(emptySms.GetText().empty());
}

TEST_CASE("Constructor with no parameters contains an empty TelephoneNumber object","[Sms]")
{
    TelephoneNumber phoneNumber = emptySms.GetTelephoneNumber();
    REQUIRE(phoneNumber.GetNumber().empty());
    REQUIRE(phoneNumber.GetCountryDialCode().empty());
    REQUIRE_FALSE(phoneNumber.ContainsCountryDialCode());
}

TEST_CASE("Constructor with all valid parameters creates a Sms object","[Sms]")
{
    REQUIRE(sms.GetContactName() == contactName);
    REQUIRE(sms.GetDateAndTime() == dateAndTime);
    REQUIRE(sms.GetType() == type);
    REQUIRE(sms.GetText() == text);
}

TEST_CASE("Constructor with a phone number contains a valid TelephoneNumber object","[Sms]")
{
    TelephoneNumber telephoneNumber = sms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == phoneNumber);
    REQUIRE_FALSE(telephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("Constructor with an empty phone number throws an exception","[Sms]")
{
    REQUIRE_THROWS(Sms(TelephoneNumber(),"Other name","02/02/2021 00:00",SmsType::outgoing,"Welcome here."));
    REQUIRE_THROWS(Sms(TelephoneNumber(""),"Other name","02/02/2021 00:00",SmsType::outgoing,"Welcome here."));
}

TEST_CASE("Constructor with an empty contact name throws an exception","[Sms]")
{
    REQUIRE_THROWS(Sms(TelephoneNumber("777888555"),"","02/02/2021 00:00",SmsType::outgoing,"Welcome here."));
}

TEST_CASE("Constructor with an empty date and time throws an exception","[Sms]")
{
    REQUIRE_THROWS(Sms(TelephoneNumber("777888555"),"Other name","",SmsType::outgoing,"Welcome here."));
}

TEST_CASE("Constructor with an empty text throws an exception","[Sms]")
{
    REQUIRE_THROWS(Sms(TelephoneNumber("777888555"),"Other name","02/02/2021 00:00",SmsType::outgoing,""));
}

TEST_CASE("Contact name is set properly","[Sms]")
{
    std::string newContactName = "Alice";
    sms.SetContactName(newContactName);
    REQUIRE(sms.GetContactName() == newContactName);
}

TEST_CASE("Date and time is set properly","[Sms]")
{
    std::string newDateAndTime = "15/05/2015 12:09";
    sms.SetDateAndTime(newDateAndTime);
    REQUIRE(sms.GetDateAndTime() == newDateAndTime);
}

TEST_CASE("Type is set properly","[Sms]")
{
    SmsType newType = SmsType::outgoing;
    sms.SetType(newType);
    REQUIRE(sms.GetType() == newType);
}

TEST_CASE("Text is set properly","[Sms]")
{
    std::string newText = "Bye Bye!";
    sms.SetText(newText);
    REQUIRE(sms.GetText() == newText);
}

TEST_CASE("Telephone number is set properly","[Sms]")
{
    std::string newPhoneNumber = "321456987", newCountryDialCode = "49";
    sms.SetTelephoneNumber(TelephoneNumber(newPhoneNumber,newCountryDialCode));
    TelephoneNumber telephoneNumber = sms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == newPhoneNumber);
    REQUIRE(telephoneNumber.GetCountryDialCode() == newCountryDialCode);
    REQUIRE(telephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("When assigning another Sms object value, the object is modifiedss","[Sms]")
{
    std::string anotherName = "Giolì & Assia", anotherDateAndTime = "25/12/2018 09:00", 
        anotherText = "Merry Xmas", anotherPhoneNumber = "005556547",
        anotherCountryDialCode = "123";
    SmsType anotherType = SmsType::outgoing;
    Sms anotherSms(TelephoneNumber(anotherPhoneNumber,anotherCountryDialCode),
        anotherName,anotherDateAndTime,anotherType,anotherText);
    sms = anotherSms;
    REQUIRE(sms.GetContactName() == anotherName);
    REQUIRE(sms.GetDateAndTime() == anotherDateAndTime);
    REQUIRE(sms.GetType() == anotherType);
    REQUIRE(sms.GetText() == anotherText);
    TelephoneNumber telephoneNumber = sms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == anotherPhoneNumber);
    REQUIRE(telephoneNumber.GetCountryDialCode() == anotherCountryDialCode);
}

TEST_CASE("When assigning the same Sms object value, the object is not modified","[Sms]")
{
    std::string phoneNumber = "5511223344557", contactName = "Jane",
    dateAndTime = "01/10/2025 14:00", text = "Buy bread, please";
    SmsType type = SmsType::outgoing;
    Sms sms(phoneNumber,contactName,dateAndTime,type,text);
    sms = sms;
    REQUIRE(sms.GetContactName() == contactName);
    REQUIRE(sms.GetDateAndTime() == dateAndTime);
    REQUIRE(sms.GetType() == type);
    REQUIRE(sms.GetText() == text);
    TelephoneNumber telephoneNumber = sms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == phoneNumber);
    REQUIRE_FALSE(telephoneNumber.ContainsCountryDialCode());
}