#include <gtest/gtest.h>
#include <filesystem>
#include "Export.h"

TEST(FileTests, FolderExists) {
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    
    std::filesystem::path path(location);
    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST(FileTests, emptyFile) {
    Export exportFile = Export();
    fileStruct fileStruct = {nullptr, 0};

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct)), false);
}

TEST(FileTests, FileCreated) {
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    std::string fileName = "TESTEXPORTFILECREATED";
    exportFile.setFileLocation(location);
    exportFile.setFileName(fileName);
    exportFile.setFileType(IFiles::type::txt);

    fileStruct fileStruct = {std::make_unique<char*>(new char[sizeof("TESTDATAHERE")]), sizeof("TESTDATAHERE")};
    strcpy(*fileStruct.fileLocation, "TESTDATAHERE");
    
    std::filesystem::path path(location + fileName + ".txt");
    EXPECT_TRUE(exportFile.exportFile(std::move(fileStruct)));
    EXPECT_TRUE(std::filesystem::exists(path));

    std::filesystem::remove(path);
}