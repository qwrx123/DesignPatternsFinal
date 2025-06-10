#include <gtest/gtest.h>
#include <filesystem>
#include "Export.h"
#include "Import.h"

TEST(FileTestsExport, FolderExists) 
{
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    
    std::filesystem::path path(location);
    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST(FileTestsExport, emptyFile) 
{
    Export exportFile = Export();
    bufferStruct fileStruct = {nullptr, 0};

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct), {}), false);
}

TEST(FileTestsExport, emptyBitmap) 
{
    Export exportFile = Export();
    exportFile.setFileType(IFiles::type::bmp);

    bufferStruct fileStruct = {std::make_unique<char[]>(sizeof("TESTDATAHERE")), sizeof("TESTDATAHERE")};

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct), 
        {.width = 0, .height = 0, .horizontalResolution = 0, .verticalResolution = 0}), false);
}

TEST(FileTestsExport, BitmapCreated) 
{
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

    std::filesystem::remove(path);
}

TEST(FileTestsExport, FileCreated) 
{
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

TEST(FileTestsExport, FileCreatedSecond) 
{
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    std::string fileName = "TESTEXPORTFILECREATED2";
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

TEST(FileTestsImport, GetBuffer) 
{
    Import importFile = Import();
    bufferStruct fileStruct = {std::make_unique<char[]>(sizeof("TESTDATAHERE")), sizeof("TESTDATAHERE")};
    strcpy(fileStruct.bufferLocation.get(), "TESTDATAHERE");
    
    ASSERT_TRUE(importFile.setBuffer(std::move(fileStruct)));
    auto [buffer, imageInfo] = importFile.getImportedData();
    
    EXPECT_EQ(buffer.bufferSize, sizeof("TESTDATAHERE"));
    EXPECT_STREQ(buffer.bufferLocation.get(), "TESTDATAHERE");
}

TEST(FileTestsImport, ReadFile) 
{
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
    ASSERT_TRUE(std::filesystem::exists(path));

    Import importFile = Import();
    importFile.setFileLocation(location);
    importFile.setFileName(fileName);
    importFile.setFileType(IFiles::type::txt);
    ASSERT_TRUE(importFile.importFile());
    auto [importedBuffer, importedImageInfo] = importFile.getImportedData();
    EXPECT_EQ(importedBuffer.bufferSize, sizeof("TESTDATAHERE"));
    EXPECT_STREQ(importedBuffer.bufferLocation.get(), "TESTDATAHERE");

    std::filesystem::remove(path);
}

TEST(FileTestsImport, GetBufferImage)
{
    bufferStruct fileStruct = {std::make_unique<char[]>(4 * 6), 4 * 6};
    bufferStruct fileStructActual = {std::make_unique<char[]>(4 * 6), 4 * 6};
    imageInfo imageInfo = {.width = 3, .height = 2, .horizontalResolution = 3780, .verticalResolution = 3780, .pixelType = pixelType::PIXEL_TYPE_RGBA};

    // Fill the buffer with some test data (e.g., a simple 2x3 pixel image)
    int* buffer = reinterpret_cast<int*>(fileStruct.bufferLocation.get());
    int* bufferActual = reinterpret_cast<int*>(fileStructActual.bufferLocation.get());
    buffer[0] = 0xFF0000FF; // Red pixel
    bufferActual[0] = buffer[0];
    buffer[1] = 0x00FF00FF; // Green pixel
    bufferActual[1] = buffer[1];
    buffer[2] = 0x0000FFFF; // Blue pixel
    bufferActual[2] = buffer[2];
    buffer[3] = 0xFFFFFFFF; // White pixel
    bufferActual[3] = buffer[3];
    buffer[4] = 0x000000FF; // Black pixel
    bufferActual[4] = buffer[4];
    buffer[5] = 0x808080FF; // Gray pixel
    bufferActual[5] = buffer[5];

    Import importFile = Import();
    importFile.setBuffer(std::move(fileStruct));
    importFile.setImageInfo(imageInfo);

    auto [importedBuffer, importedImageInfo] = importFile.getImportedData();
    EXPECT_EQ(importedBuffer.bufferSize, 4 * 6);
    EXPECT_EQ(importedImageInfo.width, 3);
    EXPECT_EQ(importedImageInfo.height, 2);
    EXPECT_EQ(importedImageInfo.horizontalResolution, 3780);
    EXPECT_EQ(importedImageInfo.verticalResolution, 3780);
    EXPECT_EQ(importedImageInfo.pixelType, pixelType::PIXEL_TYPE_RGBA);

    char* importedData = importedBuffer.bufferLocation.get();
    char* bufferActualData = fileStructActual.bufferLocation.get();
    for (size_t i = 0; i < importedBuffer.bufferSize; i++)
    {
        EXPECT_EQ(importedData[i], bufferActualData[i]);
    }
}