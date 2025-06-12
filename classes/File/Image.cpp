#include "Image.h"
#include <cstring>

Image::Image(const Image& other)
	: resolution(other.resolution),
	  dimensions(other.dimensions),
	  coordinates(other.coordinates),
	  width(other.width),
	  height(other.height),
	  pixelType(other.pixelType)
{
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	pixelData = std::make_unique<char[]>(other.width * other.height);
	std::memcpy(pixelData.get(), other.pixelData.get(), other.width * other.height);
}

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
	pixelType	= other.pixelType;

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	pixelData = std::make_unique<char[]>(other.width * other.height);
	std::memcpy(pixelData.get(), other.pixelData.get(), other.width * other.height);

	return *this;
}

bool Image::importImage(const bufferStruct& buffer, const imageInfo& image)
{
	if (buffer.bufferLocation == nullptr || buffer.bufferSize == 0)
	{
		return false;
	}

	if (image.pixelType == pixelType::PIXEL_TYPE_UNKNOWN || image.width == 0 || image.height == 0)
	{
		return false;
	}

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	pixelData = std::make_unique<char[]>(buffer.bufferSize);
	std::memcpy(pixelData.get(), buffer.bufferLocation.get(), buffer.bufferSize);

	width		= image.width;
	height		= image.height;
	pixelType	= image.pixelType;
	coordinates = {0, 0};
	dimensions	= {width, height};
	resolution	= {image.horizontalResolution, image.verticalResolution};

	return true;
}

const char* Image::getPixelData() const
{
	return pixelData.get();
}

std::pair<size_t, size_t> Image::getCoordinates() const
{
	return coordinates;
}

bool Image::setBounds(Bounds imageBounds)
{
	if (pixelData == nullptr || width == 0 || height == 0)
	{
		return false;
	}

	return false;
}

bool Image::setCoordinates(size_t x, size_t y)
{
	coordinates.first  = x;
	coordinates.second = y;
	return true;
}

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

	float horizontalChange = static_cast<float>(horizontal) / resolution.first;
	float verticalChange   = static_cast<float>(vertical) / resolution.second;
	if (horizontalChange <= 0 || verticalChange <= 0)
	{
		return false;
	}

	size_t					newWidth	 = static_cast<size_t>(width * horizontalChange);
	size_t					newHeight	 = static_cast<size_t>(height * verticalChange);
	size_t					newSize		 = newWidth * newHeight * 4;
	std::unique_ptr<char[]> newPixelData = std::make_unique<char[]>(newSize);

	char* oldData = pixelData.get();
	char* newData = newPixelData.get();

	int* oldPixel = reinterpret_cast<int*>(oldData);
	int* newPixel = reinterpret_cast<int*>(newData);

	for (size_t i = 0; i < newHeight; i++)
	{
		for (size_t j = 0; j < newWidth; j++)
		{
			size_t index	= ((i * newWidth) + j);
			size_t oldIndex = static_cast<size_t>((i / verticalChange) * width) +
							  static_cast<size_t>(j / horizontalChange);

			newPixel[index] = oldPixel[oldIndex];
		}
	}

	pixelData		  = std::move(newPixelData);
	dimensions.first  = newWidth;
	dimensions.second = newHeight;

	resolution.first  = horizontal;
	resolution.second = vertical;
	return true;
}

std::pair<size_t, size_t> Image::getDimensions() const
{
	return dimensions;
}
