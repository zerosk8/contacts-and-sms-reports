#include "utils_string.hpp"

std::string UtilsString::TrimWhiteSpacesFromStartOfString(const std::string & line)
{
    std::string lineTrimmed = line;
    if(!line.empty())
    {
         lineTrimmed = lineTrimmed.substr(lineTrimmed.find_first_not_of(WHITE_SPACES_CHARS));
    }
    return lineTrimmed;
}

std::string UtilsString::TrimWhiteSpacesFromEndOfString(const std::string & line)
{
    std::string lineTrimmed = line;
    if(!line.empty())
    {
         lineTrimmed = lineTrimmed.substr(0,lineTrimmed.find_last_not_of(WHITE_SPACES_CHARS) + 1);
    }
    return lineTrimmed;
}