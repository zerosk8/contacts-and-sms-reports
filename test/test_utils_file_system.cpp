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
        testUtilsFileSystemRelativePathToNonExistingDirectory("./test/assets/fake_directory"),
        testUtilsFileSystemAbsolutePathToNonExistingDirectory("/home/zerosk8/Desarrollo Software/Proyectos C++/contacts-and-sms-reports/test/assets/fake_directory"),
        testUtilsFileSystemCurrentDirectoryPath("/home/zerosk8/Desarrollo Software/Proyectos C++/contacts-and-sms-reports"),
        testUtilsFileSystemAbsolutePathWithDelimiter("/home/zerosk8/"),
        testUtilsFileSystemAbsolutePathWithoutDelimiter("/home/zerosk8/");
#endif

std::ifstream testUtilsFileSystemFileInputStream;

TEST_CASE("[TestUtilsFileSystem] Getting the current relative path works properly",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::GetWorkingDirectoryPath() == testUtilsFileSystemCurrentDirectoryPath);
}

TEST_CASE("[TestUtilsFileSystem] Getting the absolute directory or file path works properly when the delimiter is given in the path",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathWithDelimiter,"hello_folder") 
        == testUtilsFileSystemAbsolutePathWithDelimiter + "hello_folder");
}

TEST_CASE("[TestUtilsFileSystem] Getting the absolute directory or file path works properly when the delimiter is not given in the path",
    "[UtilsFileSystem]")
{
    #
    REQUIRE(UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathWithoutDelimiter,"hello_folder")
        == testUtilsFileSystemAbsolutePathWithoutDelimiter + "\\hello_folder");
}

TEST_CASE("[TestUtilsFileSystem] When an empty path is given, getting the absolute directory or file path returns an empty string",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::CreateStringPath("","hello_folder") == "");
}

TEST_CASE("[TestUtilsFileSystem] When an empty file or directory name is given, getting the absolute directory or file path returns an empty string",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathWithoutDelimiter,"") == "");
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing relative directory path, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        ExistsDirectory(testUtilsFileSystemRelativePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing absolute directory path, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        ExistsDirectory(testUtilsFileSystemAbsolutePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an non-existing relative directory path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectory(testUtilsFileSystemRelativePathToNonExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an non-existing absolute directory path, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectory(testUtilsFileSystemAbsolutePathToNonExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing relative directory path which is a file, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectory(testUtilsFileSystemRelativePathToExistingFile));
}

TEST_CASE("[TestUtilsFileSystem] When checking an existing absolute directory path which is a file, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        ExistsDirectory(testUtilsFileSystemAbsolutePathToExistingFile));
}

TEST_CASE("[TestUtilsFileSystem] When creating a directory path which does not exist, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::
        CreateDirectory(testUtilsFileSystemAbsolutePathToNonExistingDirectory));
    REQUIRE(std::filesystem::remove(std::filesystem::
        path(testUtilsFileSystemAbsolutePathToNonExistingDirectory)));
}

TEST_CASE("[TestUtilsFileSystem] When creating a directory path which already exists, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::
        CreateDirectory(testUtilsFileSystemAbsolutePathToExistingDirectory));
}

TEST_CASE("[TestUtilsFileSystem] When creating a directory path with non existing parent directory, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::CreateDirectory(UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathToNonExistingDirectory,
        "test_directory")));
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

TEST_CASE("[TestUtilsFileSystem] When duplicating a file which exists into a file path which does not exist, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::DuplicateFile(testUtilsFileSystemAbsolutePathToExistingFile,
        testUtilsFileSystemAbsolutePathToNonExistingFile));
    REQUIRE(std::filesystem::remove(std::filesystem::
        path(testUtilsFileSystemAbsolutePathToNonExistingFile)));
}

TEST_CASE("[TestUtilsFileSystem] When duplicating a file which exists into a file path which already exists, 'true' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE(UtilsFileSystem::DuplicateFile(
        testUtilsFileSystemAbsolutePathToExistingFile,
        UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathToExistingDirectory,
        "test_file.txt")));
}

TEST_CASE("[TestUtilsFileSystem] When duplicating a file which does not exist, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::DuplicateFile(
        testUtilsFileSystemAbsolutePathToNonExistingFile,
        UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathToExistingDirectory,
        "test_file.txt")));
}

TEST_CASE("[TestUtilsFileSystem] When duplicating a file which exists into a file path which parent directory does not exist, 'false' value is returned",
    "[UtilsFileSystem]")
{
    REQUIRE_FALSE(UtilsFileSystem::DuplicateFile(testUtilsFileSystemAbsolutePathToExistingFile,
        UtilsFileSystem::
        CreateStringPath(testUtilsFileSystemAbsolutePathToNonExistingDirectory,
        "test_file.txt")));
}
