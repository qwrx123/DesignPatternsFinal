#include "Export.h"
#include "FileLocation.h"

void Export::exportFile(void* fileLocation, ssize_t fileSize) {}

std::string Export::quarryFileLocation()
{
	return FileLocation::getDownloadLocation();
}

void Export::setFileType(IFiles::type fileType) {}
