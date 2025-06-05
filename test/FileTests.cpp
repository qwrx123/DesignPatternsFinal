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

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct), {}), false);
}

TEST(FileTests, emptyBitmap) {
    Export exportFile = Export();
    exportFile.setFileType(IFiles::type::bmp);

    fileStruct fileStruct = {std::make_unique<char*>(new char[sizeof("TESTDATAHERE")]), sizeof("TESTDATAHERE")};

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct), 
        {.width = 0, .height = 0, .horizontalResolution = 0, .verticalResolution = 0}), false);
}

TEST(FileTests, BitmapCreated) {
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    std::string fileName = "TESTEXPORTBITMAPCREATED";
    exportFile.setFileLocation(location);
    exportFile.setFileName(fileName);
    exportFile.setFileType(IFiles::type::bmp);

    fileStruct fileStruct = {std::make_unique<char*>(new char[sizeof(4 * 6)]), 4 * 6};
    imageInfo imageInfo = {.width = 3, .height = 2, .horizontalResolution = 3780, .verticalResolution = 3780};
    
    std::filesystem::path path(location + fileName + ".bmp");
    EXPECT_TRUE(exportFile.exportFile(std::move(fileStruct), imageInfo));
    EXPECT_TRUE(std::filesystem::exists(path));

    std::filesystem::remove(path);
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
    EXPECT_TRUE(exportFile.exportFile(std::move(fileStruct), {}));
    EXPECT_TRUE(std::filesystem::exists(path));

    std::filesystem::remove(path);
}