#include "FileLocation.h"
#include <string>
#include <array>

constexpr int DEFAULT_BUFFER_SIZE = 256;

#ifdef __linux__

#include <memory>
#include <cstdio>

std::string FileLocation::getDownloadLocation()
{
	std::unique_ptr<std::FILE, decltype(&pclose)> pipe(popen("xdg-user-dir DOWNLOAD", "r"), pclose);
	if (!pipe)
	{
		return {};
	}

	std::array<char, DEFAULT_BUFFER_SIZE> buffer = {0};
	std::string folderLocation;
	while (fgets(buffer.data(), sizeof(buffer), pipe.get()) != nullptr)
	{
		folderLocation += buffer.data();
	}
	if (!folderLocation.empty() && folderLocation.back() == '\n')
	{
		folderLocation.pop_back();
	}

	if (!folderLocation.empty() && folderLocation.back() != '/')
	{
		folderLocation.push_back('/');
	}

	return folderLocation;
}

#elif _WIN32

#include <shlobj_core.h>
#include <combaseapi.h>
#include <windows.h>

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

	std::array<char, DEFAULT_BUFFER_SIZE> buffer;
	WideCharToMultiByte(CP_UTF8, 0, pathPointer, -1, buffer.data(), buffer.size(), nullptr, nullptr);
	CoTaskMemFree(pathPointer);
	std::string folderLocation(buffer.data());
	if (!folderLocation.empty() && folderLocation.back() != '\\')
	{
		folderLocation.push_back('\\');
	}
	return std::move(folderLocation);
}

#endif