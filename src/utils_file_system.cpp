#include "utils_file_system.hpp"

bool UtilsFileSystem::OpenDestinationFile(std::ifstream & file,
    const std::string & filePath)
{
    if(std::filesystem::is_regular_file(std::filesystem::path(filePath)))
    {
        file.open(filePath,std::ios::in);
        return !file.fail();
    }
    return false;
}

bool UtilsFileSystem::DuplicateFile(const std::string & sourceFilePath,
    const std::string & destinationFilePath)
{
    /*
    std::ifstream originFile;
    std::ofstream destinationFile;
    originFile.open(sourceFilePath,std::ios::binary);
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
    */
    std::filesystem::path sourceFilePathObject(sourceFilePath),
        destinationFilePathObject(destinationFilePath);
    if(std::filesystem::exists(sourceFilePathObject)
        && std::filesystem::is_regular_file(sourceFilePathObject)
        && ExistsDirectory(destinationFilePathObject.parent_path().string()))
    {
        std::filesystem::remove(destinationFilePathObject);
        return std::filesystem::copy_file(sourceFilePathObject,
            destinationFilePathObject,std::filesystem::copy_options
            ::overwrite_existing);
    }
    return false;
}

bool UtilsFileSystem::ExistsDirectory(const std::string & directoryPath)
{   
    /*
    #ifdef _WIN32
        unsigned long directoryInfo = GetFileAttributesA(directoryPath.c_str());
        return !(directoryInfo == INVALID_FILE_ATTRIBUTES)
            && (directoryInfo & FILE_ATTRIBUTE_DIRECTORY);
    #else
        struct stat directoryInfo;
        return (stat(directoryPath.c_str(),&directoryInfo) == 0) && (directoryInfo.st_mode & S_IFDIR);
    #endif
    */
    std::filesystem::path pathObject(directoryPath);
    return std::filesystem::exists(pathObject) &&
        std::filesystem::is_directory(pathObject);
}

bool UtilsFileSystem::CreateDirectory(const std::string & directoryPath)
{
    /*
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
    */
   std::filesystem::path pathObject(directoryPath);
   if(ExistsDirectory(pathObject.parent_path().string()))
   {
       return std::filesystem::create_directory(std::filesystem::path(pathObject));
   }
   return false;
}

std::string UtilsFileSystem::GetWorkingDirectoryPath()
{
    //return RELATIVE_PATH_CURRENT;
    return std::filesystem::current_path().string();
}

std::string UtilsFileSystem::CreateStringPath(
    const std::string & parentDirectoryPath, const std::string & fileOrDirectoryName)
{
    if(!parentDirectoryPath.empty() && !fileOrDirectoryName.empty())
    {
        /*
        #ifdef _WIN32
            char pathDelimiter = PATH_DELIMITER_WINDOWS;
        #else
            char pathDelimiter = PATH_DELIMITER_UNIX;
        #endif
        std::string path = (parentDirectoryPath.back() != pathDelimiter)?
            parentDirectoryPath + pathDelimiter:parentDirectoryPath;
        return path + fileOrDirectoryName;
        */
       return (std::filesystem::path(parentDirectoryPath) / fileOrDirectoryName)
        .string();
    }
    return std::string();
}
