#include "FileLocation.h"

#ifndef __LINUX__

#include <memory>
#include <cstdio>

std::string FileLocation::getDownloadLocation()
{
	std::unique_ptr<std::FILE> pipe(popen("xdg-user-dir DOWNLOAD", "r"));
	if (!pipe)
	{
		return {};
	}

	char buffer[128];
	std::string folderLocation;
	while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr)
	{
		folderLocation += buffer;
	}
	if (!folderLocation.empty() && folderLocation.back() == '\n')
	{
		folderLocation.pop_back();
	}

	return folderLocation;
}

#elif _WIN32

std::string FileLocation::getDownloadLocation()
{
	return {};
}

#endif