#include "FileLocation.h"
#include <string>
#include <array>

constexpr int DEFAULT_BUFFER_SIZE = 256;

#ifdef __linux__

#include <memory>
#include <cstdio>
#include <climits>

/// @brief This function retrieves the default download location
/// @return The download path as a string
/// @note This function uses the `xdg-user-dir` command to get the download directory.
std::string FileLocation::getDownloadLocation()
{
	std::unique_ptr<std::FILE, decltype(&pclose)> pipe(popen("xdg-user-dir DOWNLOAD", "r"), pclose);
	if (!pipe)
	{
		return {};
	}

	std::array<char, DEFAULT_BUFFER_SIZE> buffer = {0};
	std::string							  folderLocation;
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

/// @brief This function retrieves the folder path of the executable
/// @return The executable folder path as a string
/// @note This function uses the `readlink` api to get the executable directory.
std::string FileLocation::getExecutableLocation()
{
	std::array<char, PATH_MAX> executableBufferPath = {0};
	size_t					   bytesRead =
		readlink("/proc/self/exe", executableBufferPath.data(), sizeof(executableBufferPath) - 1);
	if (static_cast<int>(bytesRead) == -1)
	{
		return {};
	}

	executableBufferPath.at(bytesRead) = '\0';
	std::string executablePath(executableBufferPath.data());
	while (!executablePath.empty() && executablePath.back() != '/')
	{
		executablePath.pop_back();
	}

	return executablePath;
}

#elif _WIN32

#include <shlobj_core.h>
#include <combaseapi.h>
#include <windows.h>

/// @brief This function retrieves the default download location
/// @return The download path as a string
/// @note This function uses Windows API to get the download directory.
std::string FileLocation::getDownloadLocation()
{
	PWSTR pathPointer = nullptr;

	HRESULT folderWorked = SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &pathPointer);

	if (!SUCCEEDED(folderWorked))
	{
		CoTaskMemFree(pathPointer);
		return {};
	}

	std::array<char, DEFAULT_BUFFER_SIZE> buffer{};
	WideCharToMultiByte(CP_UTF8, 0, pathPointer, -1, buffer.data(), buffer.size(), nullptr,
						nullptr);
	CoTaskMemFree(pathPointer);
	std::string folderLocation(buffer.data());
	if (!folderLocation.empty() && folderLocation.back() != '\\')
	{
		folderLocation.push_back('\\');
	}
	return std::move(folderLocation);
}

/// @brief This function retrieves the folder path of the executable
/// @return The executable folder path as a string
/// @note This function uses Windows API to get the executable directory.
std::string FileLocation::getExecutableLocation()
{
	std::array<char, MAX_PATH> executableBufferPath = {0};

	if (GetModuleFileNameA(nullptr, executableBufferPath.data(), sizeof(executableBufferPath)) == 0)
	{
		return {};
	}

	std::string executablePath(executableBufferPath.data());
	while (!executablePath.empty() && executablePath.back() != '\\')
	{
		executablePath.pop_back();
	}

	return executablePath;
}

#elif __APPLE__

#include <mach-o/dyld.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>


std::string FileLocation::getDownloadLocation()
{
	const char* home = std::getenv("HOME");
	if (!home)
	{
		return {};
	}
	std::string folderLocation = std::string(home) + "/Downloads/";
	struct stat st{};
	if (stat(folderLocation.c_str(), &st) != 0 || !S_ISDIR(st.st_mode))
	{
		return {};
	}
	return folderLocation;
}


std::string FileLocation::getExecutableLocation()
{
	char	 rawPath[PATH_MAX] = {0};
	uint32_t size			   = sizeof(rawPath);

	if (_NSGetExecutablePath(rawPath, &size) != 0)
	{
		return {};
	}

	char		resolved[PATH_MAX] = {0};
	std::string full;
	if (realpath(rawPath, resolved))
	{
		full = resolved;
	}
	else
	{
		full = rawPath;
	}
	auto pos = full.find_last_of('/');
	if (pos != std::string::npos)
	{
		full.erase(pos + 1);
	}
	return full;
}

#endif