#include <gtest/gtest.h>
#include <filesystem>
#include <cstring>
#include "Export.h"
#include "Import.h"
#include "Image.h"
#include "FileLocation.h"

TEST(FileTestsExport, FolderExists) 
{
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    
    std::filesystem::path path(location);
    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST(FileTestsFileLocation, ExecutableFolderExists) 
{
    std::string location = FileLocation::getExecutableLocation();

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

TEST(FileTestsImport, ReadBmpFile)
{
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    std::string fileName = "TESTEXPORTBMPREAD";
    exportFile.setFileLocation(location);
    exportFile.setFileName(fileName);
    exportFile.setFileType(IFiles::type::bmp);

    bufferStruct fileStruct = {std::make_unique<char[]>(4 * 6), 4 * 6};
    bufferStruct fileStructActual = {std::make_unique<char[]>(4 * 6), 4 * 6};
    imageInfo imageInfo = {.width = 3, .height = 2, .horizontalResolution = 3780, .verticalResolution = 3780, .pixelType = pixelType::PIXEL_TYPE_RGBA};

    char* bufferActual = fileStructActual.bufferLocation.get();

    // Fill the buffer with some test data (e.g., a simple 2x3 pixel image)
    int* buffer = reinterpret_cast<int*>(fileStruct.bufferLocation.get());
    buffer[0] = 0xFF0000FF; // Red pixel
    buffer[1] = 0x00FF00FF; // Green pixel
    buffer[2] = 0x0000FFFF; // Blue pixel
    buffer[3] = 0xFFFFFFFF; // White pixel
    buffer[4] = 0x000000FF; // Black pixel
    buffer[5] = 0x808080FF; // Gray pixel

    memcpy(fileStructActual.bufferLocation.get(), fileStruct.bufferLocation.get(), fileStruct.bufferSize);
    
    EXPECT_TRUE(exportFile.exportFile(std::move(fileStruct), imageInfo));
    
    Import importFile = Import();
    importFile.setFileLocation(location);
    importFile.setFileName(fileName);
    importFile.setFileType(IFiles::type::bmp);
    
    ASSERT_TRUE(importFile.importFile());
    
    auto [importedBuffer, importedImageInfo] = importFile.getImportedData();
    
    EXPECT_EQ(importedBuffer.bufferSize, 4 * 6);
    EXPECT_EQ(importedImageInfo.width, 3);
    EXPECT_EQ(importedImageInfo.height, 2);
    
    char* importedData = importedBuffer.bufferLocation.get();
    
    for (size_t i = 0; i < importedBuffer.bufferSize; i++)
    {
        EXPECT_EQ(importedData[i], bufferActual[i]);
    }

    std::filesystem::remove(location + fileName + ".bmp");
}

class FileTestsImage : public ::testing::Test
{
protected:
    Image image;
    bufferStruct fileStruct;
    bufferStruct originalData;
    imageInfo imageInfo;
    void SetUp() override
    {
        image = Image();
        fileStruct = {std::make_unique<char[]>(4 * 6), 4 * 6};
        imageInfo = {.width = 3, .height = 2, .horizontalResolution = 3780, .verticalResolution = 3780, .pixelType = pixelType::PIXEL_TYPE_RGBA};
    
        int* buffer = reinterpret_cast<int*>(fileStruct.bufferLocation.get());
        buffer[0] = 0xFF0000FF;
        buffer[1] = 0x00FF00FF; 
        buffer[2] = 0x0000FFFF; 
        buffer[3] = 0xFFFFFFFF; 
        buffer[4] = 0x000000FF; 
        buffer[5] = 0x808080FF;

        originalData = {std::make_unique<char[]>(4 * 6), 4 * 6};
        std::memcpy(originalData.bufferLocation.get(), buffer, fileStruct.bufferSize);
    }
};

TEST_F(FileTestsImage, getPixelData)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    const char* pixelData = image.getPixelData();
    
	size_t scanLineSize = imageInfo.width * 4;
	size_t iteration	= 0;

	for (const char* scanLine = pixelData + ((imageInfo.height - 1) * scanLineSize);
		 scanLine >= pixelData;
		 scanLine -= scanLineSize)
    {
        for (size_t j = 0; j < scanLineSize; j++)
        {
            EXPECT_EQ(scanLine[j], originalData.bufferLocation.get()[iteration * scanLineSize + j]);
        }
        iteration++;
	}
}

TEST_F(FileTestsImage, getDimensions)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    auto dimensions = image.getDimensions();
    
    EXPECT_EQ(dimensions.first, imageInfo.width);
    EXPECT_EQ(dimensions.second, imageInfo.height);
}

TEST_F(FileTestsImage, getCoordinates)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    auto coordinates = image.getCoordinates();
    
    EXPECT_EQ(coordinates.first, 0);
    EXPECT_EQ(coordinates.second, 0);
}

TEST_F(FileTestsImage, setCoordinates)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    size_t newX = 10;
    size_t newY = 20;
    
    ASSERT_TRUE(image.setCoordinates(newX, newY));
    
    auto coordinates = image.getCoordinates();
    
    EXPECT_EQ(coordinates.first, newX);
    EXPECT_EQ(coordinates.second, newY);
}

TEST_F(FileTestsImage, setResolution)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));

    size_t Horizontal = 2000;
    size_t Vertical = 2000;
    std::pair<size_t, size_t> dimensions = image.getDimensions();
    ASSERT_TRUE(image.setResolution(Horizontal, Vertical));

    size_t newHorizontal = 4000;
    size_t newVertical = 4000;
    ASSERT_TRUE(image.setResolution(newHorizontal, newVertical));
    std::pair<size_t, size_t> newDimensions = image.getDimensions();
    
    EXPECT_EQ(dimensions.first, newDimensions.first/2);
    EXPECT_EQ(dimensions.second, newDimensions.second/2);
}

TEST_F(FileTestsImage, importImage)
{
    EXPECT_TRUE(image.importImage(fileStruct, imageInfo));
    
    auto dimensions = image.getDimensions();
    EXPECT_EQ(dimensions.first, imageInfo.width);
    EXPECT_EQ(dimensions.second, imageInfo.height);
    
    bufferStruct emptyBuffer = {nullptr, 0};
    struct imageInfo emptyImageInfo = {};
    EXPECT_FALSE(image.importImage(emptyBuffer, emptyImageInfo));
}

TEST_F(FileTestsImage, copyConstructor)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    Image imageCopy(image);

    auto originalDimensions = image.getDimensions();
    auto copyDimensions = imageCopy.getDimensions();
    EXPECT_EQ(originalDimensions.first, copyDimensions.first);
    EXPECT_EQ(originalDimensions.second, copyDimensions.second);
    
    auto originalCoordinates = image.getCoordinates();
    auto copyCoordinates = imageCopy.getCoordinates();
    EXPECT_EQ(originalCoordinates.first, copyCoordinates.first);
    EXPECT_EQ(originalCoordinates.second, copyCoordinates.second);
    
    const char* originalPixelData = image.getPixelData();
    const char* copyPixelData = imageCopy.getPixelData();
    
    for (size_t i = 0; i < fileStruct.bufferSize; i++)
    {
        EXPECT_EQ(originalPixelData[i], copyPixelData[i]);
    }
}

TEST_F(FileTestsImage, assignmentOperator)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    Image imageAssigned;
    imageAssigned = image;
    
    auto originalDimensions = image.getDimensions();
    auto assignedDimensions = imageAssigned.getDimensions();
    EXPECT_EQ(originalDimensions.first, assignedDimensions.first);
    EXPECT_EQ(originalDimensions.second, assignedDimensions.second);
    
    auto originalCoordinates = image.getCoordinates();
    auto assignedCoordinates = imageAssigned.getCoordinates();
    EXPECT_EQ(originalCoordinates.first, assignedCoordinates.first);
    EXPECT_EQ(originalCoordinates.second, assignedCoordinates.second);
    
    const char* originalPixelData = image.getPixelData();
    const char* assignedPixelData = imageAssigned.getPixelData();
    
    for (size_t i = 0; i < fileStruct.bufferSize; i++)
    {
        EXPECT_EQ(originalPixelData[i], assignedPixelData[i]);
    }
    
    imageAssigned = imageAssigned;
    auto selfAssignedDimensions = imageAssigned.getDimensions();
    EXPECT_EQ(originalDimensions.first, selfAssignedDimensions.first);
    EXPECT_EQ(originalDimensions.second, selfAssignedDimensions.second);
}

TEST_F(FileTestsImage, setResolutionEdgeCases)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    EXPECT_FALSE(image.setResolution(0, 100));
    EXPECT_FALSE(image.setResolution(100, 0));
    EXPECT_FALSE(image.setResolution(0, 0));
    
    EXPECT_TRUE(image.setResolution(imageInfo.horizontalResolution, imageInfo.verticalResolution));
    auto originalDimensions = image.getDimensions();
    
    auto unchangedDimensions = image.getDimensions();
    EXPECT_EQ(originalDimensions.first, unchangedDimensions.first);
    EXPECT_EQ(originalDimensions.second, unchangedDimensions.second);
}

TEST_F(FileTestsImage, setResolutionScaling)
{
    ASSERT_TRUE(image.importImage(fileStruct, imageInfo));
    
    auto originalDimensions = image.getDimensions();
    
    size_t doubledHorizontal = imageInfo.horizontalResolution * 2;
    size_t doubledVertical = imageInfo.verticalResolution * 2;
    
    ASSERT_TRUE(image.setResolution(doubledHorizontal, doubledVertical));
    
    auto doubledDimensions = image.getDimensions();
    EXPECT_EQ(originalDimensions.first * 2, doubledDimensions.first);
    EXPECT_EQ(originalDimensions.second * 2, doubledDimensions.second);
}

