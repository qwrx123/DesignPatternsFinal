#include "Export.h"
#include "FileLocation.h"

void Export::exportFile(void* fileLocation, size_t fileSize) {}

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
