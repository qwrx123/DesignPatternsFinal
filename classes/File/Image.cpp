#include "Image.h"
#include <cstring>

/// @brief The constructor for the Image class
/// @param other The Image object to copy from
Image::Image(const Image& other)
	: resolution(other.resolution),
	  dimensions(other.dimensions),
	  coordinates(other.coordinates),
	  width(other.width),
	  height(other.height),
	  pixelFormat(other.pixelFormat),
	  bufferSize(other.bufferSize)
{
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	pixelData = std::make_unique<char[]>(bufferSize);
	std::memcpy(pixelData.get(), other.pixelData.get(), bufferSize);
}

/// @brief The assignment operator for the Image class
/// @param other The Image object to copy from
/// @return A reference to the current Image object
Image& Image::operator=(const Image& other)
{
	if (this == &other)
	{
		return *this;
	}

	resolution	= other.resolution;
	dimensions	= other.dimensions;
	coordinates = other.coordinates;
	width		= other.width;
	height		= other.height;
	pixelFormat = other.pixelFormat;
	bufferSize	= other.bufferSize;

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	pixelData = std::make_unique<char[]>(other.bufferSize);
	std::memcpy(pixelData.get(), other.pixelData.get(), other.bufferSize);

	return *this;
}

/// @brief A function to import an image from a buffer and image information
/// @param buffer The buffer containing the pixel data
/// @param image The image information containing width, height, and pixel type
/// @return true if the import was successful, false otherwise
bool Image::importImage(const bufferStruct& buffer, const imageInfo& image)
{
	if (buffer.bufferLocation == nullptr || buffer.bufferSize == 0)
	{
		return false;
	}

	if (image.pixelFormat == pixelType::PIXEL_TYPE_UNKNOWN || image.width == 0 || image.height == 0)
	{
		return false;
	}

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	pixelData = std::make_unique<char[]>(buffer.bufferSize);

	size_t scanLineSize = image.width * 4;
	size_t iteration	= 0;

	for (char* scanLine = pixelData.get() + ((image.height - 1) * scanLineSize);
		 scanLine >= pixelData.get();
		 scanLine -= scanLineSize)	// NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	{
		std::memcpy(scanLine, buffer.bufferLocation.get() + (scanLineSize * iteration++),
					scanLineSize);
	}

	width		= image.width;
	height		= image.height;
	bufferSize	= buffer.bufferSize;
	pixelFormat = image.pixelFormat;
	coordinates = {0, 0};
	dimensions	= {width, height};
	resolution	= {image.horizontalResolution, image.verticalResolution};

	return true;
}

/// @brief Get the pixel data of the image
/// @return A pointer to the pixel data
const char* Image::getPixelData() const
{
	return pixelData.get();
}

std::pair<size_t, size_t> Image::getCoordinates() const
{
	return coordinates;
}

/// @brief Set the bounds of the image
/// @param imageBounds The bounds to set for the image
/// @return True if the bounds were set successfully, false otherwise
bool Image::setBounds(Bounds imageBounds)
{
	if (pixelData == nullptr || width == 0 || height == 0)
	{
		return false;
	}

	return false;
}

/// @brief Set the coordinates of the image
/// @param x The x coordinate to set
/// @param y The y coordinate to set
/// @return True if successful, false otherwise
bool Image::setCoordinates(size_t x, size_t y)
{
	coordinates.first  = x;
	coordinates.second = y;
	return true;
}

/// @brief Set the resolution of the image, Scaling if nessary
/// @param horizontal The horizontal resultion to set
/// @param vertical The vertical resolution to set
/// @return True if successful, false otherwise
bool Image::setResolution(size_t horizontal, size_t vertical)
{
	if (horizontal == 0 || vertical == 0)
	{
		return false;
	}

	if (horizontal == resolution.first && vertical == resolution.second)
	{
		return true;
	}

	float horizontalChange = static_cast<float>(horizontal) / static_cast<float>(resolution.first);
	float verticalChange   = static_cast<float>(vertical) / static_cast<float>(resolution.second);
	if (horizontalChange <= 0 || verticalChange <= 0)
	{
		return false;
	}

	auto   newWidth	 = static_cast<size_t>(static_cast<float>(width) * horizontalChange);
	auto   newHeight = static_cast<size_t>(static_cast<float>(height) * verticalChange);
	size_t newSize	 = newWidth * newHeight * 4;
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	std::unique_ptr<char[]> newPixelData = std::make_unique<char[]>(newSize);

	char* oldData = pixelData.get();
	char* newData = newPixelData.get();

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	int* oldPixel = reinterpret_cast<int*>(oldData);
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	int* newPixel = reinterpret_cast<int*>(newData);

	for (size_t i = 0; i < newHeight; i++)
	{
		for (size_t j = 0; j < newWidth; j++)
		{
			size_t index	= ((i * newWidth) + j);
			size_t oldIndex = static_cast<size_t>((static_cast<float>(i) / verticalChange) *
												  static_cast<float>(width)) +
							  static_cast<size_t>(static_cast<float>(j) / horizontalChange);

			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			newPixel[index] = oldPixel[oldIndex];
		}
	}

	pixelData		  = std::move(newPixelData);
	bufferSize		  = newSize;
	dimensions.first  = newWidth;
	dimensions.second = newHeight;

	resolution.first  = horizontal;
	resolution.second = vertical;
	return true;
}

/// @brief Get the dimensions of the image
/// @return A pair containing the width and height of the image
std::pair<size_t, size_t> Image::getDimensions() const
{
	return dimensions;
}
