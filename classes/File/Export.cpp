#include "Export.h"
#include "FileLocation.h"
#include <memory>
#include <vector>

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

void Export::setFileLocation(const std::string& fileLocation)
{
	this->fileLocation = fileLocation;
}

std::string Export::quarryFileLocation()
{
	return FileLocation::getDownloadLocation();
}

void Export::setFileType(IFiles::type fileType)
{
	this->fileType = fileType;
}

void Export::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
}

bool Export::exportTxtFile(bufferStruct fileStruct)
{
	if (!fileStruct.bufferLocation || fileStruct.bufferSize == 0)
	{
		return false;
	}

	std::string				   fullpath = fileLocation + fileName + ".txt";
	std::unique_ptr<std::FILE> file(std::fopen(fullpath.c_str(), "wt"));
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

	return false;
}

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
	const WORD PADDING	 = ALIGNMENT - (((imageInfo.width * PIXEL_SIZE) / CHAR_BIT) % ALIGNMENT);

	const DWORD RED_MASK   = 0xFF000000;
	const DWORD GREEN_MASK = 0x00FF0000;
	const DWORD BLUE_MASK  = 0x0000FF00;
	const DWORD ALPHA_MASK = 0x000000FF;

	const DWORD LCS_sRGB = 0x73524742; /* 'sRGB' */

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
