#include "telephone_number.hpp"
#include "catch.hpp"

void RequireEmptyPhoneNumber(const TelephoneNumber & phoneNumber);
void RequireEmptyCountryDialCode(const TelephoneNumber & phoneNumber);

std::string testTelephoneNumberNumber = "123456789", testTelephoneNumberCountryDialCode = "34";
TelephoneNumber testTelephoneNumberValidTelephoneNumber(testTelephoneNumberNumber,
    testTelephoneNumberCountryDialCode), testTelephoneNumerAnotherValidTelephoneNumber("999888777");

TEST_CASE("[TestTelephoneNumber] Constructor with no parameters creates an empty TelephoneNumber object",
    "[TelephoneNumber]")
{
    TelephoneNumber phoneNumber;
    REQUIRE(phoneNumber.GetNumber().empty());
    RequireEmptyCountryDialCode(phoneNumber);
}

TEST_CASE("[TestTelephoneNumber] Constructor with one numeric string parameter creates a TelephoneNumber object",
    "[TelephoneNumber]")
{
    TelephoneNumber phoneNumber(testTelephoneNumberNumber);
    RequireEmptyPhoneNumber(phoneNumber);
    RequireEmptyCountryDialCode(phoneNumber);
}

TEST_CASE("[TestTelephoneNumber] Constructor with two numeric string parameters creates a TelephoneNumber object",
    "[TelephoneNumber]")
{
    RequireEmptyPhoneNumber(testTelephoneNumberValidTelephoneNumber);
    REQUIRE_FALSE(testTelephoneNumberValidTelephoneNumber.GetCountryDialCode().empty());
    REQUIRE(testTelephoneNumberValidTelephoneNumber.ContainsCountryDialCode());
}

TEST_CASE("[TestTelephoneNumber] Constructor with second empty string parameter creates a TelephoneNumber object",
    "[TelephoneNumber]")
{
    TelephoneNumber phoneNumber(testTelephoneNumberNumber,"");
    RequireEmptyPhoneNumber(phoneNumber);
    RequireEmptyCountryDialCode(phoneNumber);
}

TEST_CASE("[TestTelephoneNumber] Constructor with first non-numeric string parameter throws an exception",
    "[TelephoneNumber]")
{
    REQUIRE_THROWS(TelephoneNumber("sdfsdf74544'0&"));
}

TEST_CASE("[TestTelephoneNumber] Constructor with empty string in first parameter throws an exception",
    "[TelephoneNumber]")
{
    REQUIRE_THROWS(TelephoneNumber(""));
}

TEST_CASE("[TestTelephoneNumber] Constructor with second non-numeric string parameter throws an exception",
    "[TelephoneNumber]")
{
    REQUIRE_THROWS(TelephoneNumber(testTelephoneNumberNumber,"ac"));
}

TEST_CASE("[TestTelephoneNumber] When assigning another TelephoneNumber object value, the object is modified",
    "[TelephoneNumber]")
{
    auto secondNumber = "999888777";
    TelephoneNumber firstPhoneNumber(testTelephoneNumberNumber,testTelephoneNumberCountryDialCode),
        secondPhoneNumber(secondNumber);
    firstPhoneNumber = secondPhoneNumber;
    REQUIRE(firstPhoneNumber.GetNumber() == secondNumber);
    RequireEmptyCountryDialCode(firstPhoneNumber);
}

TEST_CASE("[TestTelephoneNumber] When assigning the same TelephoneNumber object value, the object is not modified",
    "[TelephoneNumber]")
{
    testTelephoneNumberValidTelephoneNumber = testTelephoneNumberValidTelephoneNumber;
    REQUIRE(testTelephoneNumberValidTelephoneNumber.GetNumber() == testTelephoneNumberNumber);
    REQUIRE(testTelephoneNumberValidTelephoneNumber.GetCountryDialCode() == testTelephoneNumberCountryDialCode);
}

TEST_CASE("[TestTelephoneNumber] When comparing two equal TelephoneNumber objects with equal operator, a true assertion is given",
    "[TelephoneNumber]")
{
    TelephoneNumber anotherPhoneNumber = testTelephoneNumberValidTelephoneNumber;
    REQUIRE(testTelephoneNumberValidTelephoneNumber == anotherPhoneNumber);
}

TEST_CASE("[TestTelephoneNumber] When comparing two different TelephoneNumber objects with equal operator, a false assertion is given",
    "[TelephoneNumber]")
{
    REQUIRE_FALSE(testTelephoneNumberValidTelephoneNumber == testTelephoneNumerAnotherValidTelephoneNumber);
}

TEST_CASE("[TestTelephoneNumber] When comparing two different TelephoneNumber objects with different operator, a true assertion is given",
    "[TelephoneNumber]")
{
    REQUIRE(testTelephoneNumberValidTelephoneNumber != testTelephoneNumerAnotherValidTelephoneNumber);
}

TEST_CASE("[TestTelephoneNumber] When comparing two equal TelephoneNumber objects with different operator, a false assertion is given",
    "[TelephoneNumber]")
{
    TelephoneNumber anotherPhoneNumber = testTelephoneNumberValidTelephoneNumber;
    REQUIRE_FALSE(testTelephoneNumberValidTelephoneNumber != anotherPhoneNumber);
}

void RequireEmptyPhoneNumber(const TelephoneNumber & phoneNumber)
{
    REQUIRE_FALSE(phoneNumber.GetNumber().empty());
}

void RequireEmptyCountryDialCode(const TelephoneNumber & phoneNumber)
{
    REQUIRE(phoneNumber.GetCountryDialCode().empty());
    REQUIRE_FALSE(phoneNumber.ContainsCountryDialCode());
}