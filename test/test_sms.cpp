#include "sms.hpp"
#include "catch.hpp"

std::string testSmsPhoneNumber = "123456789", testSmsContactName = "Name",
    testSmsDateAndTime = "01/01/2021 00:00", testSmsText = "Hello, World";
SmsType testSmsType = SmsType::incoming;
Sms testSmsValidSms(testSmsPhoneNumber,testSmsContactName,testSmsDateAndTime,testSmsType,testSmsText),
    testSmsAnotherValidSms(testSmsPhoneNumber,"Another name",testSmsDateAndTime,SmsType::outgoing,"Bye bye!");
Sms testSmsEmptySms;

TEST_CASE("[TestSms] Constructor with no parameters creates an empty Sms object",
    "[Sms]")
{
    REQUIRE(testSmsEmptySms.GetContactName().empty());
    REQUIRE(testSmsEmptySms.GetDateAndTime().empty());
    REQUIRE(testSmsEmptySms.GetType() == SmsType::unknown);
    REQUIRE(testSmsEmptySms.GetText().empty());
}

TEST_CASE("[TestSms] Constructor with no parameters contains an empty TelephoneNumber object",
    "[Sms]")
{
    TelephoneNumber telephoneNumber = testSmsEmptySms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber().empty());
    REQUIRE(telephoneNumber.GetCountryDialCode().empty());
    REQUIRE_FALSE(telephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("[TestSms] Constructor with all valid parameters creates a Sms object",
    "[Sms]")
{
    REQUIRE(testSmsValidSms.GetContactName() == testSmsContactName);
    REQUIRE(testSmsValidSms.GetDateAndTime() == testSmsDateAndTime);
    REQUIRE(testSmsValidSms.GetType() == testSmsType);
    REQUIRE(testSmsValidSms.GetText() == testSmsText);
}

TEST_CASE("[TestSms] Constructor with a phone number contains a valid TelephoneNumber object",
    "[Sms]")
{
    TelephoneNumber telephoneNumber = testSmsValidSms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == testSmsPhoneNumber);
    REQUIRE_FALSE(telephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("[TestSms] Constructor with an empty phone number throws an exception",
    "[Sms]")
{
    REQUIRE_THROWS(Sms(TelephoneNumber(),testSmsContactName,testSmsDateAndTime,testSmsType,testSmsText));
    REQUIRE_THROWS(Sms(TelephoneNumber(""),testSmsContactName,testSmsDateAndTime,testSmsType,testSmsText));
}

TEST_CASE("[TestSms] Constructor with an empty contact name throws an exception",
    "[Sms]")
{
    REQUIRE_THROWS(Sms(testSmsPhoneNumber,"",testSmsDateAndTime,testSmsType,testSmsText));
}

TEST_CASE("[TestSms] Constructor with an empty date and time throws an exception",
    "[Sms]")
{
    REQUIRE_THROWS(Sms(testSmsPhoneNumber,testSmsContactName,"",testSmsType,testSmsText));
}

TEST_CASE("[TestSms] Constructor with an empty text throws an exception","[Sms]")
{
    REQUIRE_THROWS(Sms(testSmsPhoneNumber,testSmsContactName,testSmsDateAndTime,testSmsType,""));
}

TEST_CASE("[TestSms] Contact name is set properly","[Sms]")
{
    std::string newContactName = "Alice";
    testSmsValidSms.SetContactName(newContactName);
    REQUIRE(testSmsValidSms.GetContactName() == newContactName);
}

TEST_CASE("[TestSms] Date and time is set properly","[Sms]")
{
    std::string newDateAndTime = "15/05/2015 12:09";
    testSmsValidSms.SetDateAndTime(newDateAndTime);
    REQUIRE(testSmsValidSms.GetDateAndTime() == newDateAndTime);
}

TEST_CASE("[TestSms] Type is set properly","[Sms]")
{
    SmsType newType = SmsType::outgoing;
    testSmsValidSms.SetType(newType);
    REQUIRE(testSmsValidSms.GetType() == newType);
}

TEST_CASE("[TestSms] Text is set properly","[Sms]")
{
    std::string newText = "Bye Bye!";
    testSmsValidSms.SetText(newText);
    REQUIRE(testSmsValidSms.GetText() == newText);
}

TEST_CASE("[TestSms] Telephone number is set properly","[Sms]")
{
    std::string newPhoneNumber = "321456987", newCountryDialCode = "49";
    testSmsValidSms.SetTelephoneNumber(TelephoneNumber(newPhoneNumber,newCountryDialCode));
    TelephoneNumber telephoneNumber = testSmsValidSms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == newPhoneNumber);
    REQUIRE(telephoneNumber.GetCountryDialCode() == newCountryDialCode);
    REQUIRE(telephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("[TestSms] When assigning another Sms object value, the object is modified",
    "[Sms]")
{
    std::string anotherName = "Giolì & Assia", anotherDateAndTime = "25/12/2018 09:00", 
        anotherText = "Merry Xmas", anotherPhoneNumber = "005556547",
        anotherCountryDialCode = "123";
    SmsType anotherType = SmsType::outgoing;
    Sms anotherSms(TelephoneNumber(anotherPhoneNumber,anotherCountryDialCode),
        anotherName,anotherDateAndTime,anotherType,anotherText);
    testSmsValidSms = anotherSms;
    REQUIRE(testSmsValidSms.GetContactName() == anotherName);
    REQUIRE(testSmsValidSms.GetDateAndTime() == anotherDateAndTime);
    REQUIRE(testSmsValidSms.GetType() == anotherType);
    REQUIRE(testSmsValidSms.GetText() == anotherText);
    TelephoneNumber telephoneNumber = testSmsValidSms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == anotherPhoneNumber);
    REQUIRE(telephoneNumber.GetCountryDialCode() == anotherCountryDialCode);
}

TEST_CASE("[TestSms] When assigning the same Sms object value, the object is not modified",
    "[Sms]")
{
    std::string phoneNumber = "5511223344557", testSmsContactName = "Jane",
    testSmsDateAndTime = "01/10/2025 14:00", testSmsText = "Buy bread, please";
    SmsType testSmsType = SmsType::outgoing;
    Sms sms(phoneNumber,testSmsContactName,testSmsDateAndTime,testSmsType,testSmsText);
    sms = sms;
    REQUIRE(sms.GetContactName() == testSmsContactName);
    REQUIRE(sms.GetDateAndTime() == testSmsDateAndTime);
    REQUIRE(sms.GetType() == testSmsType);
    REQUIRE(sms.GetText() == testSmsText);
    TelephoneNumber telephoneNumber = sms.GetTelephoneNumber();
    REQUIRE(telephoneNumber.GetNumber() == phoneNumber);
    REQUIRE_FALSE(telephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("[TestSms] When comparing two equal Sms objects with equal operator, a true assertion is given",
    "[Sms]")
{
    Sms anotherSms = testSmsValidSms;
    REQUIRE(anotherSms == testSmsValidSms);
}

TEST_CASE("[TestSms] When comparing two different Sms objects with equal operator, a false assertion is given",
    "[Sms]")
{
    REQUIRE_FALSE(testSmsAnotherValidSms == testSmsValidSms);
}

TEST_CASE("[TestSms] When comparing two different Sms objects with different operator, a true assertion is given",
    "[Sms]")
{
    REQUIRE(testSmsAnotherValidSms != testSmsValidSms);
}

TEST_CASE("[TestSms] When comparing two equal Sms objects with different operator, a false assertion is given",
    "[Sms]")
{
    Sms anotherSms = testSmsValidSms;
    REQUIRE_FALSE(anotherSms != testSmsValidSms);
}
