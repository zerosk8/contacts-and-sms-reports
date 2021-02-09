#include "catch.hpp"
#include "telephone_number.hpp"

void RequireEmptyPhoneNumber(const TelephoneNumber & phoneNumber);
void RequireEmptyCountryDialCode(const TelephoneNumber & phoneNumber);

TEST_CASE("Constructor with no parameters creates an empty TelephoneNumber object","[TelephoneNumber]")
{
    TelephoneNumber phoneNumber;
    REQUIRE(phoneNumber.GetNumber().empty());
    RequireEmptyCountryDialCode(phoneNumber);
}

TEST_CASE("Constructor with one numeric string parameter creates a TelephoneNumber object","[TelephoneNumber]")
{
    TelephoneNumber phoneNumber("123456789");
    RequireEmptyPhoneNumber(phoneNumber);
    RequireEmptyCountryDialCode(phoneNumber);
}

TEST_CASE("Constructor with two numeric string parameters creates a TelephoneNumber object","[TelephoneNumber]")
{
    TelephoneNumber phoneNumber("123456789","34");
    RequireEmptyPhoneNumber(phoneNumber);
    REQUIRE_FALSE(phoneNumber.GetCountryDialCode().empty());
    REQUIRE(phoneNumber.ContainsCountryDialCode());
}

TEST_CASE("Constructor with second empty string parameter creates a TelephoneNumber object","[TelephoneNumber]")
{
    TelephoneNumber phoneNumber("123456789","");
    RequireEmptyPhoneNumber(phoneNumber);
    RequireEmptyCountryDialCode(phoneNumber);
}

TEST_CASE("Constructor with first non-numeric string parameter throws an exception","[TelephoneNumber]")
{
    REQUIRE_THROWS(TelephoneNumber("sdfsdf74544'0&"));
}

TEST_CASE("Constructor with empty string in first parameter throws an exception","[TelephoneNumber]")
{
    REQUIRE_THROWS(TelephoneNumber(""));
}

TEST_CASE("Constructor with second non-numeric string parameter throws an exception","[TelephoneNumber]")
{
    REQUIRE_THROWS(TelephoneNumber("112233445566","ac"));
}

TEST_CASE("When assigning another value, the object is modified","[TelephoneNumber]")
{
    auto secondNumber = "999888777";
    TelephoneNumber firstPhoneNumber("111222333","34"), secondPhoneNumber(secondNumber);
    firstPhoneNumber = secondPhoneNumber;
    REQUIRE(firstPhoneNumber.GetNumber() == secondNumber);
    RequireEmptyCountryDialCode(firstPhoneNumber);
}

TEST_CASE("When assigning the same value, the object is not modified","[TelephoneNumber]")
{
    auto number = "35477889911", coutryDialCode = "124";
    TelephoneNumber phoneNumber(number,coutryDialCode);
    phoneNumber = phoneNumber;
    REQUIRE(phoneNumber.GetNumber() == number);
    REQUIRE(phoneNumber.GetCountryDialCode() == coutryDialCode);
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