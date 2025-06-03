#include "Export.h"
#include "FileLocation.h"
#include <memory>

bool Export::exportFile(fileStruct fileStruct)
{
	if (!fileStruct.fileLocation || fileStruct.fileSize == 0)
	{
		return false;
	}

	std::string				   fullpath = fileLocation + fileName + ".txt";
	std::unique_ptr<std::FILE> file(std::fopen(fullpath.c_str(), "wt"));
	if (!file)
	{
		return false;
	}

	if (std::fwrite(*fileStruct.fileLocation, sizeof(char), fileStruct.fileSize, file.get()) !=
		fileStruct.fileSize)
	{
		return false;
	}

	return true;
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
