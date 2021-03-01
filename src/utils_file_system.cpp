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
    std::filesystem::path pathObject(directoryPath);
    return std::filesystem::exists(pathObject) &&
        std::filesystem::is_directory(pathObject);
}

bool UtilsFileSystem::CreateDirectory(const std::string & directoryPath)
{
    std::filesystem::path pathObject(directoryPath);
    if(ExistsDirectory(pathObject.parent_path().string()))
    {
        return std::filesystem::create_directory(std::filesystem::path(pathObject));
    }
    return false;
}

std::string UtilsFileSystem::GetWorkingDirectoryPath()
{
    return std::filesystem::current_path().string();
}

std::string UtilsFileSystem::CreateStringPath(
    const std::string & parentDirectoryPath, const std::string & fileOrDirectoryName)
{
    if(!parentDirectoryPath.empty() && !fileOrDirectoryName.empty())
    {
        return (std::filesystem::path(parentDirectoryPath) / fileOrDirectoryName)
            .string();
    }
    return std::string();
}
