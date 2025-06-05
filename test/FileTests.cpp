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
    bufferStruct fileStruct = {nullptr, 0};

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct), {}), false);
}

TEST(FileTests, emptyBitmap) {
    Export exportFile = Export();
    exportFile.setFileType(IFiles::type::bmp);

    bufferStruct fileStruct = {std::make_unique<char[]>(sizeof("TESTDATAHERE")), sizeof("TESTDATAHERE")};

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

    bufferStruct fileStruct = {std::make_unique<char[]>(4 * 6), 4 * 6};
    imageInfo imageInfo = {.width = 3, .height = 2, .horizontalResolution = 3780, .verticalResolution = 3780, .pixelType = pixelType::PIXEL_TYPE_RGBA};

    // Fill the buffer with some test data (e.g., a simple 2x3 pixel image)
    int* buffer = reinterpret_cast<int*>(fileStruct.bufferLocation.get());
    buffer[0] = 0xFF0000FF; // Red pixel
    buffer[1] = 0x00FF00FF; // Green pixel
    buffer[2] = 0x0000FFFF; // Blue pixel
    buffer[3] = 0xFFFFFFFF; // White pixel
    buffer[4] = 0x000000FF; // Black pixel
    buffer[5] = 0x808080FF; // Gray pixel
    
    std::filesystem::path path(location + fileName + ".bmp");
    EXPECT_TRUE(exportFile.exportFile(std::move(fileStruct), imageInfo));
    EXPECT_TRUE(std::filesystem::exists(path));

    //std::filesystem::remove(path);
}

TEST(FileTests, FileCreated) {
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    std::string fileName = "TESTEXPORTFILECREATED";
    exportFile.setFileLocation(location);
    exportFile.setFileName(fileName);
    exportFile.setFileType(IFiles::type::txt);

    bufferStruct fileStruct = {std::make_unique<char[]>(sizeof("TESTDATAHERE")), sizeof("TESTDATAHERE")};
    strcpy(fileStruct.bufferLocation.get(), "TESTDATAHERE");
    
    std::filesystem::path path(location + fileName + ".txt");
    EXPECT_TRUE(exportFile.exportFile(std::move(fileStruct), {}));
    EXPECT_TRUE(std::filesystem::exists(path));

    std::filesystem::remove(path);
}