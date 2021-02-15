#include <vector>
#include "catch.hpp"
#include "contact.hpp"

std::string testContactPhoneNumber = "123456789", testContactCountryDialCode = "32",
    testContactName = "Name", testContactDateAndTime = "01/01/2021 00:00",
    testContactText = "Hello, World", testContactEmailAddress;
SmsType testContactType = SmsType::incoming;
TelephoneNumber testContactValidTelphoneNumber(testContactPhoneNumber,
    testContactCountryDialCode);
Sms testContactValidSms(testContactValidTelphoneNumber,testContactName,
    testContactDateAndTime,testContactType,testContactText);

TEST_CASE("Constructor with no parameters creates an empty Conctact object","[Contact]")
{
    Contact emptyContact;
    REQUIRE(emptyContact.GetName().empty());
    REQUIRE(emptyContact.GetListOfTelephoneNumbers().empty());
    REQUIRE(emptyContact.GetListOfEmailAddresses().empty());
    REQUIRE(emptyContact.GetListOfSms().empty());
}

TEST_CASE("Constructor with all valid parameters creates a Contact object","[Contact]")
{
    Contact validContact(testContactName,
        std::vector<TelephoneNumber>({testContactValidTelphoneNumber}),
        std::vector<std::string>({testContactEmailAddress}),
        std::vector<Sms>({testContactValidSms}));
    REQUIRE(validContact.GetName() == testContactName);
    REQUIRE(validContact.GetListOfTelephoneNumbers().size() == 1);
    REQUIRE(validContact.GetListOfEmailAddresses().size() == 1);
    REQUIRE(validContact.GetListOfSms().size() == 1);
}

TEST_CASE("Constructor missing list of sms creates a Contact object","[Contact]")
{
    Contact validContact(testContactName,
        std::vector<TelephoneNumber>({testContactValidTelphoneNumber}),
        std::vector<std::string>({testContactEmailAddress}));
    REQUIRE(validContact.GetName() == testContactName);
    REQUIRE(validContact.GetListOfTelephoneNumbers().size() == 1);
    REQUIRE(validContact.GetListOfEmailAddresses().size() == 1);
    REQUIRE(validContact.GetListOfSms().empty());
}

TEST_CASE("Constructor missing list of email addresses and list of sms creates a Contact object","[Contact]")
{
    Contact validContact(testContactName,std::vector<TelephoneNumber>({testContactValidTelphoneNumber}));
    REQUIRE(validContact.GetName() == testContactName);
    REQUIRE(validContact.GetListOfTelephoneNumbers().size() == 1);
    REQUIRE(validContact.GetListOfEmailAddresses().empty());
    REQUIRE(validContact.GetListOfSms().empty());
}

TEST_CASE("Constructor with an empty contact name throws an exception","[Contact]")
{
    REQUIRE_THROWS(Contact("",std::vector<TelephoneNumber>({testContactValidTelphoneNumber})));
}

TEST_CASE("Constructor with an empty list of telephone numbers throws an exception","[Contact]")
{
    REQUIRE_THROWS(Contact(testContactName,std::vector<TelephoneNumber>()));
}
