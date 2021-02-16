#include "utils_string.hpp"

std::string UtilsString::TrimWhiteSpacesFromStartOfString(const std::string & line)
{
    return (!line.empty())?line.substr(line.find_first_not_of(WHITE_SPACES_CHARS))
        :line;
}

std::string UtilsString::TrimWhiteSpacesFromEndOfString(const std::string & line)
{
    return (!line.empty())?line.substr(0,line.find_last_not_of(WHITE_SPACES_CHARS) + 1)
        :line;
}
