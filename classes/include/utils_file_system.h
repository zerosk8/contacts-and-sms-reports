#ifndef _UTILS_FILE_SYSTEM_H_
#define _UTILS_FILE_SYSTEM_H_
#include <fstream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

const char WINDOWS_PATH_DELIMITER = '\\';
const char UNIX_PATH_DELIMITER = '/';

class UtilsFileSystem
{
    public:
        bool OpenDestinationFile(std::ifstream & file, char * fileName);
        bool CopyFile(const std::string & originFilePath, const std::string & destinationFilePath);
        bool ExistsDirectoryPath(const std::string & directoryPath);
        bool CreateDirectoryPath(const std::string & directoryPath);
        std::string GetCurrentDirectoryPath();
        std::string GetFileOrDirectoryPathString(const std::string & parentDirectoryPath, 
        const std::string & directoryName);
};

#endif