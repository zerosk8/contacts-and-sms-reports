#include "utils_file_system.hpp"

bool UtilsFileSystem::OpenDestinationFile(std::ifstream & file, const char * fileName)
{
    file.open(fileName,std::ios::in);
    return !file.fail();
}

bool UtilsFileSystem::CopyFile(const std::string & originFilePath, const std::string & destinationFilePath)
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
    struct stat directoryInfo;
    return ((stat(directoryPath.c_str(),&directoryInfo) == 0) && (directoryInfo.st_mode & S_IFDIR));
}

bool UtilsFileSystem::CreateDirectoryPath(const std::string & directoryPath)
{
    #if defined(_WIN32)
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

std::string UtilsFileSystem::GetCurrentDirectoryPath()
{
    return CURRENT_DIRECTORY_PATH;
}

std::string UtilsFileSystem::GetFileOrDirectoryPathString(const std::string & parentDirectoryPath, 
const std::string & directoryName)
{
    if(!parentDirectoryPath.empty())
    {
        std::string path = parentDirectoryPath;
        #if defined(_WIN32)
            (path[path.size() - 1] != WINDOWS_PATH_DELIMITER)?path += WINDOWS_PATH_DELIMITER:path;
        #else
            (path[path.size() - 1] != UNIX_PATH_DELIMITER)?path += UNIX_PATH_DELIMITER:path;
        #endif
        return path + directoryName;
    }
    return std::string();
}