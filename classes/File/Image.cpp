#include "Image.h"

bool Image::importImage(const bufferStruct& buffer, const imageInfo& image)
{
	return false;
}

const char* const Image::getPixelData()
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

std::pair<size_t, size_t> Image::getDimensions() const
{
	return dimensions
}
