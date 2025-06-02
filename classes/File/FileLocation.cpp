#include "FileLocation.h"
#include <string>

#ifdef __linux__

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

#include <shlobj_core.h>
#include <combaseapi.h>

std::string FileLocation::getDownloadLocation()
{
	HRESULT folderWorked;
	PWSTR pathPointer = nullptr;

	folderWorked = SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &pathPointer);

	if (!SUCCEEDED(folderWorked))
	{
		CoTaskMemFree(pathPointer);
		return {};
	}

	std::string folderLocation = std::string(pathPointer);
	CoTaskMemFree(pathPointer);
	return folderLocation;
}

#endif