#include "utils_string.hpp"
#include "catch.hpp"

std::string testUtilsStringStringWithNoSpaces = "Hello, this is a normal string.",
    testUtilsStringWithSpacesOnStart = "     Hello, this is a normal string.",
    testUtilsStringWithSpacesOnEnd = "Hello, this is a normal string.       ",
    testUtilsStringWithTabsOnStart = "\t\tHello, this is a normal string.",
    testUtilsStringWithTabsOnEnd = "Hello, this is a normal string.\t\t\t\t",
    testUtilsStringWithNewlineCharsOnStart = "\n\n\nHello, this is a normal string.",
    testUtilsStringWithNewlineCharsOnEnd = "Hello, this is a normal string.\n\n\n";

TEST_CASE("[TestUtilsString] When a string with no spaces on start, TrimWhiteSpacesFromStartOfString returns the same string",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromStartOfString(testUtilsStringStringWithNoSpaces) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When a string with spaces on start, TrimWhiteSpacesFromStartOfString returns a string with no spaces on start",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromStartOfString(testUtilsStringWithSpacesOnStart) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When a string with tabs on start, TrimWhiteSpacesFromStartOfString returns a string with no tabs on start",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromStartOfString(testUtilsStringWithTabsOnStart) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When a string with new line chars on start, TrimWhiteSpacesFromStartOfString returns a string with no new line chars on start",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromStartOfString(testUtilsStringWithNewlineCharsOnStart) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When a string with no spaces on end, TrimWhiteSpacesFromEndOfString returns the same string",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromEndOfString(testUtilsStringStringWithNoSpaces) == testUtilsStringStringWithNoSpaces);
}
/**/
TEST_CASE("[TestUtilsString] When a string with spaces on end, TrimWhiteSpacesFromEndOfString returns a string with no spaces on end",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromEndOfString(testUtilsStringWithSpacesOnEnd) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When a string with tabs on end, TrimWhiteSpacesFromEndOfString returns a string with no tabs on end",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromEndOfString(testUtilsStringWithTabsOnEnd) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When a string with new line chars on end, TrimWhiteSpacesFromEndOfString returns a string with no new line chars on end",
    "[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromEndOfString(testUtilsStringWithNewlineCharsOnEnd) == testUtilsStringStringWithNoSpaces);
}

TEST_CASE("[TestUtilsString] When an empty string is given, TrimWhiteSpacesFromStartOfString returns an empty string","[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromStartOfString(std::string()) == "");
}

TEST_CASE("[TestUtilsString] When an empty string is given, TrimWhiteSpacesFromEndOfString returns an empty string","[UtilsString]")
{
    REQUIRE(UtilsString::TrimWhiteSpacesFromEndOfString(std::string()) == "");
}