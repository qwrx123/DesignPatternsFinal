#include "Import.h"
#include "FileLocation.h"

bool Import::importFile(const std::string& fileLocation)
{
    return false;
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