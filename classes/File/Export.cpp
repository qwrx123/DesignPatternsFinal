#include "Export.h"
#include "FileLocation.h"

void exportFile(void* fileLocation, ssize_t fileSize) {}

std::string quarryFileLocation()
{
	return FileLocation::getDownloadLocation();
}
