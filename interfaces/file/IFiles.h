#pragma once

#include <string>
#include <cstdint>
#include <memory>

struct fileStruct
{
	std::unique_ptr<char*> fileLocation;
	size_t				   fileSize;
};

/// @brief Structure to hold image information
/// @details This structure contains the width, height, and resolution of an image.
struct imageInfo
{
	size_t width;
	size_t height;
	size_t horizontalResolution;
	size_t verticalResolution;
}

#include <stdint.h>

using BYTE	= uint8_t;
using DWORD = uint32_t;
using LONG	= int32_t;
using WORD	= uint16_t;

using BITMAPINFOHEADER = struct
{
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};

class IFiles
{
   public:
	enum class type : std::uint8_t
	{
		daisy,
		jpg,
		png,
		bmp,
		txt
	};

	IFiles()						 = default;
	virtual ~IFiles()				 = default;
	IFiles(const IFiles&)			 = default;
	IFiles& operator=(const IFiles&) = default;
	IFiles(IFiles&&)				 = default;
	IFiles& operator=(IFiles&&)		 = default;

	[[nodiscard]] virtual std::string quarryFileLocation()				  = 0;
	virtual void					  setFileType(IFiles::type)			  = 0;
	virtual void					  setFileName(const std::string&)	  = 0;
	virtual void					  setFileLocation(const std::string&) = 0;
};