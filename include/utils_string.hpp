#ifndef _UTILS_STRING_HPP_
#define _UTILS_STRING_HPP_
#include <string>

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

const std::string WHITE_SPACES_CHARS = " \t\r\n";

class UtilsString
{
    public:
        static std::string TrimWhiteSpacesFromStartOfString(const std::string & line);
        static std::string TrimWhiteSpacesFromEndOfString(const std::string & line);
};

#endif
