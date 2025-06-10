#include "Import.h"
#include "FileLocation.h"

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

std::pair<bufferStruct, imageInfo> Import::getImportedData()
{
	return {std::move(importedBuffer), importedImageInfo};
}

std::string Import::quarryFileLocation()
{
	return FileLocation::getDownloadLocation();
}

void Import::setFileLocation(const std::string& fileLocation)
{
	this->fileLocation = fileLocation;
}

void Import::setFileType(IFiles::type fileType)
{
	this->fileType = fileType;
}

void Import::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
}

bool Import::setBuffer(bufferStruct buffer)
{
	importedBuffer = std::move(buffer);
	return true;
}

bool Import::setImageInfo(imageInfo info)
{
	importedImageInfo = info;
	return true;
}

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

bool Import::readBmpFile()
{
	std::string							  fullpath = fileLocation + fileName + ".txt";
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

	return true;
}

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

bool Import::validateBmpV1Header(const char* buffer, size_t buffer_size)
{
	// Need to reinterpret the buffer to access the BITMAPINFOHEADER
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	const auto* infoHeader =
		reinterpret_cast<const BITMAPINFOHEADER*>(buffer + sizeof(BITMAPFILEHEADER));

	if (infoHeader->biSize != sizeof(BITMAPINFOHEADER))
	{
		return false;
	}

	if (infoHeader->biBitCount != 24)
	{
		return false;  // Only support 24-bit and 32-bit BMP files
	}
}

bool Import::validateBmpV5Header(const char* buffer, size_t buffer_size)
{
	return false;
}
