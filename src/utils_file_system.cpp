#include "utils_file_system.hpp"

bool UtilsFileSystem::OpenDestinationFile(std::ifstream & file,
    const std::string & filePath)
{
    file.open(filePath,std::ios::in);
    return !file.fail();
}

bool UtilsFileSystem::CopyFile(const std::string & originFilePath,
    const std::string & destinationFilePath)
{
    std::ifstream originFile;
    std::ofstream destinationFile;
    originFile.open(originFilePath,std::ios::binary);
    if(originFile.fail())
    {
        return false;
    }
    destinationFile.open(destinationFilePath,std::ios::binary);
    if(destinationFile.fail())
    {
        return false;
    }
    destinationFile << originFile.rdbuf();
    originFile.close();
    destinationFile.close();
    return true;
}

bool UtilsFileSystem::ExistsDirectoryPath(const std::string & directoryPath)
{   
    #ifdef _WIN32
        unsigned long directoryInfo = GetFileAttributesA(directoryPath.c_str());
        return !(directoryInfo == INVALID_FILE_ATTRIBUTES)
            && (directoryInfo & FILE_ATTRIBUTE_DIRECTORY);
    #else
        struct stat directoryInfo;
        return (stat(directoryPath.c_str(),&directoryInfo) == 0) && (directoryInfo.st_mode & S_IFDIR);
    #endif
}

bool UtilsFileSystem::CreateDirectoryPath(const std::string & directoryPath)
{
    #ifdef _WIN32
        if(_mkdir(directoryPath.c_str()) == -1)
        {
            return false;
        }
    #else
        if(mkdir(directoryPath.c_str(),S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1)
        {
            return false;
        }
    #endif
    return true;
}

std::string UtilsFileSystem::GetCurrentRelativePath()
{
    return RELATIVE_PATH_CURRENT;
}

std::string UtilsFileSystem::GetFileOrDirectoryPathString(
    const std::string & parentDirectoryPath, const std::string & fileOrDirectoryName)
{
    if(!parentDirectoryPath.empty() && !fileOrDirectoryName.empty())
    {
        #ifdef _WIN32
            char pathDelimiter = PATH_DELIMITER_WINDOWS;
        #else
            char pathDelimiter = PATH_DELIMITER_UNIX;
        #endif
        std::string path = (parentDirectoryPath.back() != pathDelimiter)?
            parentDirectoryPath + pathDelimiter:parentDirectoryPath;
        return path + fileOrDirectoryName;
    }
    return std::string();
}
