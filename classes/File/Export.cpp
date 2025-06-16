#include "Export.h"
#include "FileLocation.h"
#include <memory>
#include <vector>
#include <cstring>
#include <iostream>

/// @brief The constructor for the Export class.
/// @param fileStruct The structure containing the file data to be exported.
/// @param imageInfo The structure containing image information.
/// @return True if the export was successful, false otherwise.
bool Export::exportFile(bufferStruct fileStruct, imageInfo imageInfo)
{
	switch (fileType)
	{
		case IFiles::type::txt:
			return exportTxtFile(std::move(fileStruct));
		case IFiles::type::bmp:
			return exportBmpFile(std::move(fileStruct), imageInfo);
		default:
			return false;
	}
}

/// @brief Sets the file location for the export.
/// @param fileLocation The location where the file will be saved.
void Export::setFileLocation(const std::string& fileLocation)
{
	this->fileLocation = fileLocation;
}

/// @brief Used to query the default file location for exporting files.
/// @return The default file location as a string.
std::string Export::quarryFileLocation()
{
	return FileLocation::getDownloadLocation();
}

/// @brief Sets the file type for the export.
/// @param fileType The type of file to be exported.
void Export::setFileType(IFiles::type fileType)
{
	this->fileType = fileType;
}

/// @brief Sets the file name for the export.
/// @param fileName The name of the file to be exported, without extension.
void Export::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
}

/// @brief Exports a text file with the given buffer structure.
/// @param fileStruct The structure containing the text data to be exported.
/// @return	 True if the export was successful, false otherwise.
bool Export::exportTxtFile(bufferStruct fileStruct)
{
	if (!fileStruct.bufferLocation || fileStruct.bufferSize == 0)
	{
		return false;
	}

	std::string							  fullpath = fileLocation + fileName + ".txt";
	std::unique_ptr<FILE, int (*)(FILE*)> file(std::fopen(fullpath.c_str(), "wt"), &fclose);
	if (!file)
	{
		return false;
	}

	if (std::fwrite(fileStruct.bufferLocation.get(), sizeof(char), fileStruct.bufferSize,
					file.get()) != fileStruct.bufferSize)
	{
		return false;
	}

	return true;
}

/// @brief Exports a BMP file with the given pixel data and image information.
/// @param pixels The structure containing the pixel data to be exported.
/// @param imageInfo The structure containing image information.
/// @return True if the export was successful, false otherwise.
bool Export::exportBmpFile(bufferStruct pixels, imageInfo imageInfo)
{
	if (!pixels.bufferLocation || pixels.bufferSize == 0)
	{
		return false;
	}
	if (imageInfo.pixelType == pixelType::PIXEL_TYPE_UNKNOWN ||
		imageInfo.pixelType != pixelType::PIXEL_TYPE_RGBA)
	{
		return false;
	}

	std::vector<char> bmpBuffer(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER) +
								pixels.bufferSize);

	char* buffer = bmpBuffer.data();

	setupBmpFileHeader(buffer, bmpBuffer.size(), imageInfo);
	setupBmpV5Header(buffer, bmpBuffer.size(), imageInfo);

	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
	auto* bmpHeader		 = reinterpret_cast<BITMAPFILEHEADER*>(buffer);
	DWORD offsetToPixels = bmpHeader->bfOffBits;

	if (bmpBuffer.size() < offsetToPixels + pixels.bufferSize)
	{
		return false;
	}

	auto* bmpV5Header = reinterpret_cast<BITMAPV5HEADER*>(buffer + sizeof(BITMAPFILEHEADER));
	WORD  pixelSize	  = bmpV5Header->bV5BitCount / CHAR_BIT;

	char* pixelData = buffer + offsetToPixels;

	for (char* scanLine = pixelData + ((imageInfo.height - 1) * imageInfo.width * pixelSize);
		 scanLine >= pixelData; scanLine -= imageInfo.width * pixelSize)
	{
		size_t currentRow =
			pixelData + ((imageInfo.height - 1) * imageInfo.width * pixelSize) - scanLine;
		std::memcpy(scanLine, pixels.bufferLocation.get() + currentRow,
					imageInfo.width * pixelSize);
	}

	std::string							  fullpath = fileLocation + fileName + ".bmp";
	std::unique_ptr<FILE, int (*)(FILE*)> file(std::fopen(fullpath.c_str(), "wb"), &fclose);
	if (!file)
	{
		return false;
	}

	if (std::fwrite(buffer, sizeof(char), bmpBuffer.size(), file.get()) != bmpBuffer.size())
	{
		return false;
	}

	return true;

	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
	// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

/// @brief Sets up the BMP file header in the provided buffer.
/// @param buffer The buffer where the BMP file header will be written.
/// @param buffer_size The size of the buffer.
/// @param imageInfo The structure containing image information.
/// @return True if the header was set up successfully, false otherwise.
bool Export::setupBmpFileHeader(char* buffer, size_t buffer_size, imageInfo imageInfo)
{
	if (buffer_size < sizeof(BITMAPFILEHEADER))
	{
		return false;
	}

	const WORD bitmapMagicStart = 0x4D42;  // 'BM'

	// Only way to make the struct correct
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	auto* fileHeader		= reinterpret_cast<BITMAPFILEHEADER*>(buffer);
	fileHeader->bfType		= bitmapMagicStart;
	fileHeader->bfSize		= static_cast<DWORD>(buffer_size);
	fileHeader->bfReserved1 = 0;
	fileHeader->bfReserved2 = 0;
	fileHeader->bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER);
	return true;
}

/// @brief Sets up the BMP V1 header in the provided buffer.
/// @param buffer The buffer where the BMP V1 header will be written.
/// @param buffer_size The size of the buffer.
/// @param imageInfo The structure containing image information.
/// @return	 True if the header was set up successfully, false otherwise.
bool Export::setupBmpV1Header(char* buffer, size_t buffer_size, imageInfo imageInfo)
{
	if (buffer_size < sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))
	{
		return false;
	}

	const WORD PIXEL_SIZE  = 24;
	const LONG COMPRESSION = 0;

	const WORD ALIGNMENT = 4;
	const WORD PADDING	 = ALIGNMENT - (((imageInfo.width * PIXEL_SIZE) / CHAR_BIT) % ALIGNMENT);

	// Move the buffer pointer to the start of the BITMAPINFOHEADER
	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	buffer += sizeof(BITMAPFILEHEADER);
	// Only way to make the struct correct
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	auto* infoHeader		  = reinterpret_cast<BITMAPINFOHEADER*>(buffer);
	infoHeader->biSize		  = sizeof(BITMAPINFOHEADER);
	infoHeader->biWidth		  = static_cast<LONG>(imageInfo.width);
	infoHeader->biHeight	  = static_cast<LONG>(imageInfo.height);
	infoHeader->biPlanes	  = 1;
	infoHeader->biBitCount	  = static_cast<WORD>(PIXEL_SIZE);
	infoHeader->biCompression = COMPRESSION;
	infoHeader->biSizeImage =
		imageInfo.height * ((imageInfo.width * (PIXEL_SIZE / CHAR_BIT)) + PADDING);
	infoHeader->biXPelsPerMeter = static_cast<LONG>(imageInfo.horizontalResolution);
	infoHeader->biYPelsPerMeter = static_cast<LONG>(imageInfo.verticalResolution);
	infoHeader->biClrUsed		= 0;
	infoHeader->biClrImportant	= 0;

	return true;
}

/// @brief Sets up the BMP V5 header in the provided buffer.
/// @param buffer The buffer where the BMP V5 header will be written.
/// @param buffer_size The size of the buffer.
/// @param imageInfo The structure containing image information.
/// @return True if the header was set up successfully, false otherwise.
bool Export::setupBmpV5Header(char* buffer, size_t buffer_size, imageInfo imageInfo)
{
	if (buffer_size < sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER))
	{
		return false;
	}

	setupBmpV1Header(buffer, buffer_size, imageInfo);

	const WORD PIXEL_SIZE  = 32;
	const LONG COMPRESSION = 3;

	const WORD ALIGNMENT = 4;
	const WORD PADDING	 = (imageInfo.width * (PIXEL_SIZE / CHAR_BIT)) % ALIGNMENT;

	const DWORD RED_MASK   = 0x000000FF;
	const DWORD GREEN_MASK = 0x0000FF00;
	const DWORD BLUE_MASK  = 0x00FF0000;
	const DWORD ALPHA_MASK = 0xFF000000;

	const DWORD LCS_sRGB = 0x73524742;

	// Move the buffer pointer to the start of the BITMAPINFOHEADER
	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	buffer += sizeof(BITMAPFILEHEADER);
	// Only way to make the struct correct
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	auto* infoHeader		   = reinterpret_cast<BITMAPV5HEADER*>(buffer);
	infoHeader->bV5Size		   = sizeof(BITMAPV5HEADER);
	infoHeader->bV5BitCount	   = static_cast<WORD>(PIXEL_SIZE);
	infoHeader->bV5Compression = COMPRESSION;
	infoHeader->bV5SizeImage =
		imageInfo.height * ((imageInfo.width * (PIXEL_SIZE / CHAR_BIT)) + PADDING);
	infoHeader->bV5RedMask	   = RED_MASK;
	infoHeader->bV5GreenMask   = GREEN_MASK;
	infoHeader->bV5BlueMask	   = BLUE_MASK;
	infoHeader->bV5AlphaMask   = ALPHA_MASK;
	infoHeader->bV5CSType	   = LCS_sRGB;
	infoHeader->bV5Endpoints   = {.ciexyzRed   = {.ciexyzX = 0, .ciexyzY = 0, .ciexyzZ = 0},
								  .ciexyzGreen = {.ciexyzX = 0, .ciexyzY = 0, .ciexyzZ = 0},
								  .ciexyzBlue  = {.ciexyzX = 0, .ciexyzY = 0, .ciexyzZ = 0}};
	infoHeader->bV5GammaRed	   = 0;
	infoHeader->bV5GammaGreen  = 0;
	infoHeader->bV5GammaBlue   = 0;
	infoHeader->bV5Intent	   = 0;
	infoHeader->bV5ProfileData = 0;
	infoHeader->bV5ProfileSize = 0;
	infoHeader->bV5Reserved	   = 0;

	return true;
}
