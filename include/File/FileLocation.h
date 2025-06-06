#ifndef FILELOCATION_H
#define FILELOCATION_H

#include <string>

/// @brief This class provides static methods to retrieve operating system specific file locations.
class FileLocation
{
   public:
	FileLocation() = delete;
	static std::string getDownloadLocation();
};

#endif	// FILELOCATION_H