#ifndef _UTILS_FILE_SYSTEM_HPP_
#define _UTILS_FILE_SYSTEM_HPP_
#include <fstream>
#include <string>
#include <string.h>
#include <sys/types.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

const char PATH_DELIMITER_WINDOWS = '\\';
const char PATH_DELIMITER_UNIX = '/';
const std::string RELATIVE_PATH_CURRENT = ".";

class UtilsFileSystem
{
    public:
        static bool OpenDestinationFile(std::ifstream & file,
            const std::string & filePath);
        static bool CopyFile(const std::string & originFilePath,
            const std::string & destinationFilePath);
        static bool ExistsDirectoryPath(const std::string & directoryPath);
        static bool CreateDirectoryPath(const std::string & directoryPath);
        static std::string GetCurrentRelativePath();
        static std::string GetFileOrDirectoryPathString(
            const std::string & parentDirectoryPath,
            const std::string & fileOrDirectoryName);
};

#endif