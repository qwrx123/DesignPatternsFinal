#include "Export.h"
#include "FileLocation.h"
#include <memory>

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

	std::unique_ptr<char[]> exportFile = std::make_unique<char[]>(
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPV5HEADER) + pixels.bufferSize);

	return false;
}

bool Export::setupBmpV1Header(char* buffer, size_t buffer_size, imageInfo imageInfo)
{
	return false;
}

bool Export::setupBmpV5Header(char* buffer, size_t buffer_size, imageInfo imageInfo)
{
	return false;
}
