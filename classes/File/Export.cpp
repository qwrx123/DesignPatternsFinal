#include "Export.h"
#include "FileLocation.h"
#include <memory>

bool Export::exportFile(fileStruct fileStruct)
{
	if (!fileStruct.fileLocation || fileStruct.fileSize == 0)
	{
		return false;
	}
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
