#include <vector>
#include "contact.hpp"
#include "catch.hpp"

std::string testContactPhoneNumber = "123456789", testContactCountryDialCode = "32",
    testContactName = "Name", testContactDateAndTime = "01/01/2021 00:00",
    testContactText = "Hello, World", testContactEmailAddress;
SmsType testContactType = SmsType::incoming;
TelephoneNumber testContactValidTelephoneNumber(testContactPhoneNumber,
    testContactCountryDialCode);
Sms testContactValidSms(testContactValidTelephoneNumber,testContactName,
    testContactDateAndTime,testContactType,testContactText);
Contact testContactEmptyContact, testContactValidContact(testContactName,
    std::vector<TelephoneNumber>({testContactValidTelephoneNumber})),
    testContactAnotherValidContact("Contact 1",
    std::vector<TelephoneNumber>({TelephoneNumber("777888999")}));

TEST_CASE("[TestContact] Constructor with no parameters creates an empty Conctact object",
    "[Contact]")
{
    REQUIRE(testContactEmptyContact.GetName().empty());
    REQUIRE(testContactEmptyContact.GetListOfTelephoneNumbers().empty());
    REQUIRE(testContactEmptyContact.GetListOfEmailAddresses().empty());
    REQUIRE(testContactEmptyContact.GetListOfSms().empty());
}

TEST_CASE("[TestContact] Constructor with all valid parameters creates a Contact object",
    "[Contact]")
{
    Contact validContact(testContactName,
        std::vector<TelephoneNumber>({testContactValidTelephoneNumber}),
        std::vector<std::string>({testContactEmailAddress}),
        std::vector<Sms>({testContactValidSms}));
    REQUIRE(validContact.GetName() == testContactName);
    REQUIRE(validContact.GetListOfTelephoneNumbers().size() == 1);
    REQUIRE(validContact.GetListOfEmailAddresses().size() == 1);
    REQUIRE(validContact.GetListOfSms().size() == 1);
}

TEST_CASE("[TestContact] Constructor missing list of sms creates a Contact object",
    "[Contact]")
{
    Contact validContact(testContactName,
        std::vector<TelephoneNumber>({testContactValidTelephoneNumber}),
        std::vector<std::string>({testContactEmailAddress}));
    REQUIRE(validContact.GetName() == testContactName);
    REQUIRE(validContact.GetListOfTelephoneNumbers().size() == 1);
    REQUIRE(validContact.GetListOfEmailAddresses().size() == 1);
    REQUIRE(validContact.GetListOfSms().empty());
}

TEST_CASE("[TestContact] Constructor missing list of email addresses and list of sms creates a Contact object",
    "[Contact]")
{
    Contact validContact(testContactName,std::vector<TelephoneNumber>({testContactValidTelephoneNumber}));
    REQUIRE(validContact.GetName() == testContactName);
    REQUIRE(validContact.GetListOfTelephoneNumbers().size() == 1);
    REQUIRE(validContact.GetListOfEmailAddresses().empty());
    REQUIRE(validContact.GetListOfSms().empty());
}

TEST_CASE("[TestContact] Constructor with an empty contact name throws an exception",
    "[Contact]")
{
    REQUIRE_THROWS(Contact("",std::vector<TelephoneNumber>({testContactValidTelephoneNumber})));
}

TEST_CASE("[TestContact] Constructor with an empty list of telephone numbers throws an exception",
    "[Contact]")
{
    REQUIRE_THROWS(Contact(testContactName,std::vector<TelephoneNumber>()));
}

TEST_CASE("[TestContact] Name is set properly","[Contact]")
{
    std::string newName = "New Name";
    testContactEmptyContact.SetName(newName);
    REQUIRE(testContactEmptyContact.GetName() == newName);
}

TEST_CASE("[TestContact] ListOfTelephoneNumbers is set properly","[Contact]")
{
    std::vector<TelephoneNumber> newListOfTelephoneNumbers
        {TelephoneNumber("555444222","1"),TelephoneNumber("666999888","35")};
    testContactEmptyContact.SetListOfTelephoneNumbers(newListOfTelephoneNumbers);
    REQUIRE(testContactEmptyContact.GetListOfTelephoneNumbers() ==
        newListOfTelephoneNumbers);
}

TEST_CASE("[TestContact] ListOfEmailAddresses is set properly","[Contact]")
{
    std::vector<std::string> newListOfEmailAddresses{"first@server.com","second@one.es"};
    testContactEmptyContact.SetListOfEmailAddresses(newListOfEmailAddresses);
    REQUIRE(testContactEmptyContact.GetListOfEmailAddresses() == newListOfEmailAddresses);
}

TEST_CASE("[TestContact] ListOfSms is set properly","[Contact]")
{
    std::vector<Sms> newListOfSms{testContactValidSms};
    testContactEmptyContact.SetListOfSms(newListOfSms);
    REQUIRE(testContactEmptyContact.GetListOfSms() == newListOfSms);
}

TEST_CASE("[TestContact] Telephone numbers are added properly","[Contact]")
{
    Contact emptyContact;
    emptyContact.AddTelephoneNumber(testContactValidTelephoneNumber);
    auto listOfTelephoneNumbers = emptyContact.GetListOfTelephoneNumbers();
    REQUIRE(listOfTelephoneNumbers.size() == 1);
    REQUIRE(listOfTelephoneNumbers[0] == testContactValidTelephoneNumber);
}

TEST_CASE("[TestContact] Sms are added properly","[Contact]")
{
    Contact emptyContact;
    emptyContact.AddSms(testContactValidSms);
    auto listOfSms = emptyContact.GetListOfSms();
    REQUIRE(listOfSms.size() == 1);
    REQUIRE(listOfSms[0] == testContactValidSms);
}

TEST_CASE("[TestSms] When assigning another Contact object value, the object is modified",
    "[Sms]")
{
    Contact validContact = testContactValidContact;
    validContact = testContactAnotherValidContact;
    REQUIRE(validContact.GetName() == testContactAnotherValidContact.GetName());
    REQUIRE(validContact.GetListOfTelephoneNumbers() ==
        testContactAnotherValidContact.GetListOfTelephoneNumbers());
    REQUIRE(validContact.GetListOfEmailAddresses() ==
        testContactAnotherValidContact.GetListOfEmailAddresses());
    REQUIRE(validContact.GetListOfSms() ==
        testContactAnotherValidContact.GetListOfSms());
}

TEST_CASE("[TestSms] When assigning the same Contact object value, the object is not modified",
    "[Sms]")
{
    testContactValidContact = testContactValidContact;
    REQUIRE(testContactValidContact.GetName() == testContactName);
    auto listOfSms = testContactValidContact.GetListOfTelephoneNumbers();
    REQUIRE(listOfSms.size() == 1);
    REQUIRE(listOfSms[0] == testContactValidTelephoneNumber);
}
