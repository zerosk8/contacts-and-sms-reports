#include "utils_file_system.hpp"
#include "catch.hpp"

#ifdef _WIN32
    std::string testUtilsFileSystemRelativePathToExistingFile(".\\test\\assets\\example_file.txt"),
        testUtilsFileSystemAbsolutePathToExistingFile("D:\\zerosk8\\Desarrollo Software\\Proyectos C++\\contacts-and-sms-reports\\test\\assets\\example_file.txt"),
        testUtilsFileSystemRelativePathToNonExistingFile(".\\test\\assets\\fake_file.txt"),
        testUtilsFileSystemAbsolutePathToNonExistingFile("D:\\zerosk8\\Desarrollo Software\\Proyectos C++\\contacts-and-sms-reports\\test\\assets\\fake_file.txt"),
        testUtilsFileSystemRelativePathToExistingDirectory(".\\test\\assets\\example_directory"),
        testUtilsFileSystemAbsolutePathToExistingDirectory("D:\\zerosk8\\Desarrollo Software\\Proyectos C++\\contacts-and-sms-reports\\test\\assets\\example_directory"),
        testUtilsFileSystemRelativePathToNonExistingDirectory(".\\test\\assets\\fake_directory"),
        testUtilsFileSystemAbsolutePathToNonExistingDirectory("D:\\zerosk8\\Desarrollo Software\\Proyectos C++\\contacts-and-sms-reports\\test\\assets\\fake_directory"),
        testUtilsFileSystemCurrentDirectoryPath("D:\\zerosk8\\Desarrollo Software\\Proyectos C++\\contacts-and-sms-reports"),
        testUtilsFileSystemAbsolutePathWithDelimiter("D:\\zerosk8\\"),
        testUtilsFileSystemAbsolutePathWithoutDelimiter("D:\\zerosk8");
#else
    std::string testUtilsFileSystemRelativePathToExistingFile("./test/assets/example_file.txt"),
        testUtilsFileSystemAbsolutePathToExistingFile("/home/zerosk8/Desarrollo Software/Proyectos C++/contacts-and-sms-reports/test/assets/example_file.txt"),
        testUtilsFileSystemRelativePathToNonExistingFile("./test/assets/fake_file.txt"),
        testUtilsFileSystemAbsolutePathToNonExistingFile("/home/zerosk8/Desarrollo Software/Proyectos C++/contacts-and-sms-reports/test/assets/fake_file.txt"),
        testUtilsFileSystemRelativePathToExistingDirectory("./test/assets/example_directory"),
        testUtilsFileSystemAbsolutePathToExistingDirectory("/home/zerosk8/Desarrollo Software/Proyectos C++/contacts-and-sms-reports/test/assets/example_directory"),
        testUtilsFileSystemAbsolutePathWithDelimiter("/home/zerosk8/"),
        testUtilsFileSystemAbsolutePathWithoutDelimiter("/home/zerosk8/");
#endif

std::ifstream testUtilsFileSystemFileInputStream;

TEST_CASE("[TestUtilsFileSystem] Getting the current relative path works properly",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::GetCurrentRelativePath() == ".");
}

TEST_CASE("[TestUtilsFileSystem] Getting the absolute directory or file path works properly when the delimiter is given in the path",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        GetFileOrDirectoryPathString(testUtilsFileSystemAbsolutePathWithDelimiter,"hello_folder") 
        == testUtilsFileSystemAbsolutePathWithDelimiter + "hello_folder");
}

TEST_CASE("[TestUtilsFileSystem] Getting the absolute directory or file path works properly when the delimiter is not given in the path",
    "[UtilsFileSystem]")
{
    #
    REQUIRE(UtilsFileSystem::
        GetFileOrDirectoryPathString(testUtilsFileSystemAbsolutePathWithoutDelimiter,"hello_folder")
        == testUtilsFileSystemAbsolutePathWithoutDelimiter + "\\hello_folder");
}

TEST_CASE("[TestUtilsFileSystem] When an empty path is given, getting the absolute directory or file path returns an empty string",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::GetFileOrDirectoryPathString("","hello_folder") == "");
}

TEST_CASE("[TestUtilsFileSystem] When an empty file or directory name is given, getting the absolute directory or file path returns an empty string",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        GetFileOrDirectoryPathString(testUtilsFileSystemAbsolutePathWithoutDelimiter,"") == "");
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing relative directory path, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        ExistsDirectoryPath(testUtilsFileSystemRelativePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing absolute directory path, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        ExistsDirectoryPath(testUtilsFileSystemAbsolutePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an non-existing relative directory path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectoryPath(testUtilsFileSystemRelativePathToNonExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an non-existing absolute directory path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectoryPath(testUtilsFileSystemAbsolutePathToNonExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing relative directory path which is a file, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectoryPath(testUtilsFileSystemRelativePathToExistingFile));
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing absolute directory path which is a file, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectoryPath(testUtilsFileSystemAbsolutePathToExistingFile));
}

TEST_CASE("[TestUtilsFileSystem] When opening an existing relative file path, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,
        testUtilsFileSystemRelativePathToExistingFile));
    testUtilsFileSystemFileInputStream.close();
}

TEST_CASE("[TestUtilsFileSystem] When opening an existing absolute file path, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,
        testUtilsFileSystemAbsolutePathToExistingFile));
    testUtilsFileSystemFileInputStream.close();
}

TEST_CASE("[TestUtilsFileSystem] When opening a non-existing relative file path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,
        testUtilsFileSystemRelativePathToNonExistingFile));
}

TEST_CASE("[TestUtilsFileSystem] When opening a non-existing absolute file path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,
        testUtilsFileSystemAbsolutePathToNonExistingFile));
}

TEST_CASE("[TestUtilsFileSystem] When opening an existing relative file path which is a directory, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,
        testUtilsFileSystemRelativePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When opening an existing absolute file path which is a directory, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,
        testUtilsFileSystemAbsolutePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When opening an empty file path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        OpenDestinationFile(testUtilsFileSystemFileInputStream,""));
}
