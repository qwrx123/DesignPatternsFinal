#include "Import.h"
#include "FileLocation.h"

bool Import::importFile()
{
    switch (fileType)
    {
        case IFiles::type::txt:
            return readTxtFile();
        case IFiles::type::bmp:
            return false;
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

    
}
