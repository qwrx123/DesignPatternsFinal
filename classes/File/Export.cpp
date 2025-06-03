#include "Export.h"
#include "FileLocation.h"
#include <memory>

bool Export::exportFile(std::unique_ptr<char*> fileLocation, size_t fileSize)
{
	return true;
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
