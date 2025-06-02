#ifndef FILELOCATION_H
#define FILELOCATION_H

#include <string>

class FileLocation
{
   public:
	FileLocation() = delete;
	static std::string getDownloadLocation();
};

#endif	// FILELOCATION_H