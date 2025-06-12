#include "Image.h"

bool Image::importImage(const bufferStruct& buffer, const imageInfo& image)
{
	if (buffer.bufferLocation == nullptr || buffer.bufferSize == 0)
    {
        return false;
    }

    if (image.pixelType == pixelType::PIXEL_TYPE_UNKNOWN || image.width == 0 ||
        image.height == 0)
    {
        return false;
    }

    pixelData = std::make_unique<char[]>(buffer.bufferSize);
    std::memcpy(pixelData.get(), buffer.bufferLocation.get(), buffer.bufferSize);

    width		 = image.width;
    height		 = image.height;
    pixelType	 = image.pixelType;
    coordinates	= {0, 0};
    dimensions	= {width, height};
    resolution	= {image.horizontalResolution, image.verticalResolution};

    return true;
}

const char* const Image::getPixelData() const
{
	return pixelData.get();
}

std::pair<size_t, size_t> Image::getCoordinates() const
{
    return coordinates;
}

bool Image::setBounds(Bounds)
{
	if (pixelData == nullptr || width == 0 || height == 0)
    {
        return false;
    }

    return false;
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

    resolution.first  = horizontal;
    resolution.second = vertical;
    return true;
}

std::pair<size_t, size_t> Image::getDimensions() const
{
	return dimensions
}
