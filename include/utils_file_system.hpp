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

const char WINDOWS_PATH_DELIMITER = '\\';
const char UNIX_PATH_DELIMITER = '/';
const std::string CURRENT_DIRECTORY_PATH = ".";

class UtilsFileSystem
{
    public:
        bool OpenDestinationFile(std::ifstream & file, const char * fileName);
        bool CopyFile(const std::string & originFilePath, const std::string & destinationFilePath);
        bool ExistsDirectoryPath(const std::string & directoryPath);
        bool CreateDirectoryPath(const std::string & directoryPath);
        std::string GetCurrentDirectoryPath();
        std::string GetFileOrDirectoryPathString(const std::string & parentDirectoryPath, 
        const std::string & directoryName);
};

#endif