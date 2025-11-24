#include "Import.h"
#include "FileLocation.h"
#include <cstring>

/// @brief Imports a file based on the file name and location and type stored in the class.
/// @return True if the import was successful, false otherwise.
bool Import::importFile()
{
	switch (fileType)
	{
		case IFiles::type::txt:
			return readTxtFile();
		case IFiles::type::bmp:
			return readBmpFile();
		default:
			return false;
	}
}

/// @brief Gets the imported data as a pair of bufferStruct and imageInfo.
/// @return	 A pair containing the imported buffer and image information.
std::pair<bufferStruct, imageInfo> Import::getImportedData()
{
	return {std::move(importedBuffer), importedImageInfo};
}

/// @brief Used to query the default file location for exporting files.
/// @return The default file location as a string.
std::string Import::quarryFileLocation()
{
	return FileLocation::getDownloadLocation();
}

/// @brief Used to set the file location for the import.
/// @param fileLocation The location where the file is stored.
void Import::setFileLocation(const std::string& fileLocation)
{
	this->fileLocation = fileLocation;
}

/// @brief Sets the file type for the import.
/// @param fileType The type of file to be imported.
void Import::setFileType(IFiles::type fileType)
{
	this->fileType = fileType;
}

/// @brief Sets the file name for the import.
/// @param fileName	 The name of the file to be imported, without extension.
void Import::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
}

/// @brief Sets the imported data buffer directly.
/// @param buffer The buffer structure containing the data to be imported.
/// @return True if the buffer was set successfully, false otherwise.
bool Import::setBuffer(bufferStruct buffer)
{
	importedBuffer = std::move(buffer);
	return true;
}

/// @brief Sets the image information for the imported file.
/// @param info The imageInfo structure containing the image details.
/// @return	 True if the image information was set successfully, false otherwise.
bool Import::setImageInfo(imageInfo info)
{
	importedImageInfo = info;
	return true;
}

/// @brief Reads a text file from the specified location and stores its content in the buffer.
/// @return True if the file was read successfully, false otherwise.
bool Import::readTxtFile()
{
	std::string							  fullpath = fileLocation + fileName + ".txt";
	std::unique_ptr<FILE, int (*)(FILE*)> file(std::fopen(fullpath.c_str(), "rt"), &fclose);
	if (!file)
	{
		return false;
	}

	if (std::fseek(file.get(), 0, SEEK_END) != 0)
	{
		return false;
	}

	long fileSize = std::ftell(file.get());
	if (fileSize == -1)
	{
		return false;
	}

	if (std::fseek(file.get(), 0, SEEK_SET) != 0)
	{
		return false;
	}

	importedBuffer.bufferSize = static_cast<size_t>(fileSize);
	// When working with files and raw memory, it is neccisary touse char[]
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	importedBuffer.bufferLocation = std::make_unique<char[]>(importedBuffer.bufferSize);

	// Read file content
	size_t readBytes = std::fread(importedBuffer.bufferLocation.get(), sizeof(char),
								  importedBuffer.bufferSize, file.get());

	return readBytes == importedBuffer.bufferSize;
}

/// @brief Reads a BMP file from the specified location and validates its headers.
/// @return True if the BMP file was read and validated successfully, false otherwise.
bool Import::readBmpFile()
{
	std::string							  fullpath = fileLocation + fileName + ".bmp";
	std::unique_ptr<FILE, int (*)(FILE*)> file(std::fopen(fullpath.c_str(), "rb"), &fclose);
	if (!file)
	{
		return false;
	}

	if (std::fseek(file.get(), 0, SEEK_END) != 0)
	{
		return false;
	}

	long fileSizeWithErrorCheck = std::ftell(file.get());
	if (fileSizeWithErrorCheck == -1)
	{
		return false;
	}

	auto fileSize = static_cast<size_t>(fileSizeWithErrorCheck);
	if (std::fseek(file.get(), 0, SEEK_SET) != 0)
	{
		return false;
	}

	// When working with files and raw memory, it is neccisary touse char[]
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	std::unique_ptr<char[]> fileBuffer = std::make_unique<char[]>(fileSize);

	// Read file content
	size_t readBytes = std::fread(fileBuffer.get(), sizeof(char), fileSize, file.get());

	if (readBytes != fileSize)
	{
		return false;
	}

	if (fileSize < sizeof(BITMAPFILEHEADER))
	{
		return false;
	}

	if (!validateBmpHeader(fileBuffer.get(), fileSize))
	{
		return false;
	}

	if (fileSize < sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))
	{
		return false;
	}

	// Need to reinterpret the buffer to access the BITMAPINFOHEADER
	auto* infoHeader =	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		reinterpret_cast<BITMAPINFOHEADER*>(fileBuffer.get() + sizeof(BITMAPFILEHEADER));

	DWORD size = infoHeader->biSize;

	switch (size)
	{
		case sizeof(BITMAPINFOHEADER):
			if (!validateBmpV1Header(fileBuffer.get(), fileSize))
			{
				return false;
			}
			break;
		case sizeof(BITMAPV5HEADER):
			if (!validateBmpV5Header(fileBuffer.get(), fileSize))
			{
				return false;
			}
			break;
		default:
			return false;  // Unsupported BMP version
	}

	return readBmpV5PixelData(fileBuffer.get(), fileSize) && size == sizeof(BITMAPV5HEADER);
}

/// @brief Validates the BMP file header.
/// @param buffer The buffer containing the BMP file data.
/// @param buffer_size The size of the buffer containing the BMP file data.
/// @return True if the BMP header is valid, false otherwise.
bool Import::validateBmpHeader(const char* buffer, size_t buffer_size)
{
	// Need to reinterpret the buffer to access the BITMAPINFOHEADER
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	const auto* fileHeader = reinterpret_cast<const BITMAPFILEHEADER*>(buffer);

	const WORD bitmapMagicStart = 0x4D42;  // 'BM'
	if (fileHeader->bfType != bitmapMagicStart)
	{
		return false;
	}

	if (fileHeader->bfOffBits > buffer_size)
	{
		return false;
	}

	if (fileHeader->bfSize != buffer_size)
	{
		return false;
	}

	return true;
}

/// @brief Validates the BMP V1 header.
/// @param buffer The buffer containing the BMP file data.
/// @param buffer_size The size of the buffer containing the BMP file data.
/// @return True if the BMP V1 header is valid, false otherwise.
bool Import::validateBmpV1Header(const char* buffer, size_t buffer_size)
{
	// Need to reinterpret the buffer to access the BITMAPINFOHEADER
	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	const auto* infoHeader =
		reinterpret_cast<const BITMAPINFOHEADER*>(buffer + sizeof(BITMAPFILEHEADER));

	// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

	if (infoHeader->biSize != sizeof(BITMAPINFOHEADER))
	{
		return false;
	}

	if (infoHeader->biPlanes != 1)
	{
		return false;
	}

	if (infoHeader->biCompression != 0)
	{
		return false;
	}

	const WORD validBitCount = 24;
	if (infoHeader->biBitCount != validBitCount)
	{
		return false;
	}

	if (infoHeader->biSizeImage != 0 &&
		infoHeader->biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) !=
			buffer_size)
	{
		return false;
	}

	return true;
}

/// @brief Validates the BMP V5 header.
/// @param buffer The buffer containing the BMP file data.
/// @param buffer_size The size of the buffer containing the BMP file data.
/// @return True if the BMP V5 header is valid, false otherwise.
bool Import::validateBmpV5Header(const char* buffer, size_t buffer_size)
{
	// Need to reinterpret the buffer to access the BITMAPINFOHEADER
	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	const auto* infoHeader =
		reinterpret_cast<const BITMAPV5HEADER*>(buffer + sizeof(BITMAPFILEHEADER));

	// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

	if (infoHeader->bV5Size != sizeof(BITMAPV5HEADER))
	{
		return false;
	}

	if (infoHeader->bV5Planes != 1)
	{
		return false;
	}

	const WORD validBitCount = 32;
	if (infoHeader->bV5BitCount != validBitCount)
	{
		return false;
	}

	if (infoHeader->bV5Compression != 3)
	{
		return false;
	}

	if (infoHeader->bV5GreenMask == 0 || infoHeader->bV5RedMask == 0 ||
		infoHeader->bV5BlueMask == 0 || infoHeader->bV5AlphaMask == 0)
	{
		return false;
	}

	const DWORD LCS_sRGB = 0x73524742;	// 'sRGB' in little-endian
	const DWORD LCS_WIN	 = 0x57696E20;	// 'Win ' in little-endian
	if (infoHeader->bV5CSType != LCS_sRGB && infoHeader->bV5CSType != LCS_WIN)
	{
		return false;
	}

	if (infoHeader->bV5SizeImage != 0 &&
		infoHeader->bV5SizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER) != buffer_size)
	{
		return false;
	}

	return true;
}

/// @brief Reads the pixel data from a BMP V5 file and stores it in the importedBuffer.
/// @param buffer The buffer containing the BMP file data.
/// @param buffer_size The size of the buffer containing the BMP file data.
/// @return True if the pixel data was read successfully, false otherwise.
bool Import::readBmpV5PixelData(const char* buffer, size_t buffer_size)
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
	const auto* infoHeader = reinterpret_cast<const BITMAPV5HEADER*>(buffer);

	const auto* V5Header =
		reinterpret_cast<const BITMAPV5HEADER*>(buffer + sizeof(BITMAPFILEHEADER));

	const char* pixelData = buffer + V5Header->bV5Size + sizeof(BITMAPFILEHEADER);

	importedBuffer.bufferSize = V5Header->bV5SizeImage;
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	importedBuffer.bufferLocation = std::make_unique<char[]>(importedBuffer.bufferSize);

	char* importedPixelData = importedBuffer.bufferLocation.get();

	size_t iteration = 0;
	size_t scanLineSize =
		(V5Header->bV5BitCount / static_cast<size_t>(CHAR_BIT)) * V5Header->bV5Width;
	for (char* scanLine = importedPixelData + ((V5Header->bV5Height - 1) * scanLineSize);
		 scanLine >= importedPixelData; scanLine -= scanLineSize)
	{
		std::memcpy(scanLine, pixelData + (scanLineSize * iteration++), scanLineSize);
	}

	importedImageInfo.width				   = V5Header->bV5Width;
	importedImageInfo.height			   = V5Header->bV5Height;
	importedImageInfo.horizontalResolution = V5Header->bV5XPelsPerMeter;
	importedImageInfo.verticalResolution   = V5Header->bV5YPelsPerMeter;
	importedImageInfo.pixelFormat		   = pixelType::PIXEL_TYPE_RGBA;

	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
	// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	return true;
}
