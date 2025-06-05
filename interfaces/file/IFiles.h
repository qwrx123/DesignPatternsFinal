#pragma once

#include <string>
#include <cstdint>
#include <memory>

enum class pixelType : std::uint8_t
{
	PIXEL_TYPE_UNKNOWN = 0,
	PIXEL_TYPE_RGB,
	PIXEL_TYPE_RGBA,
	PIXEL_TYPE_ARGB,
	PIXEL_TYPE_BGR,
	PIXEL_TYPE_BGRA,
	PIXEL_TYPE_ABGR
};

struct bufferStruct
{
	std::unique_ptr<char[]> bufferLocation = nullptr;
	size_t					bufferSize	   = 0;
};

/// @brief Structure to hold image information
/// @details This structure contains the width, height, and resolution of an image.
struct imageInfo
{
	size_t	  width				   = 0;
	size_t	  height			   = 0;
	size_t	  horizontalResolution = 0;
	size_t	  verticalResolution   = 0;
	pixelType pixelType			   = pixelType::PIXEL_TYPE_UNKNOWN;
};

#include <stdint.h>

using BYTE	= uint8_t;
using DWORD = uint32_t;
using LONG	= int32_t;
using WORD	= uint16_t;

using BITMAPFILEHEADER = struct
{
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
};

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

using FXPT2DOT30 = LONG;

using CIEXYZ = struct
{
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
};

using CIEXYZTRIPLE = struct
{
	CIEXYZ ciexyzRed;
	CIEXYZ ciexyzGreen;
	CIEXYZ ciexyzBlue;
};

using BITMAPV5HEADER = struct
{
	DWORD		 bV5Size;
	LONG		 bV5Width;
	LONG		 bV5Height;
	WORD		 bV5Planes;
	WORD		 bV5BitCount;
	DWORD		 bV5Compression;
	DWORD		 bV5SizeImage;
	LONG		 bV5XPelsPerMeter;
	LONG		 bV5YPelsPerMeter;
	DWORD		 bV5ClrUsed;
	DWORD		 bV5ClrImportant;
	DWORD		 bV5RedMask;
	DWORD		 bV5GreenMask;
	DWORD		 bV5BlueMask;
	DWORD		 bV5AlphaMask;
	DWORD		 bV5CSType;
	CIEXYZTRIPLE bV5Endpoints;
	DWORD		 bV5GammaRed;
	DWORD		 bV5GammaGreen;
	DWORD		 bV5GammaBlue;
	DWORD		 bV5Intent;
	DWORD		 bV5ProfileData;
	DWORD		 bV5ProfileSize;
	DWORD		 bV5Reserved;
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