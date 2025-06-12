#include "Image.h"

bool Image::importImage(const bufferStruct& buffer, const imageInfo& image)
{
	return false;
}

const char* const Image::getPixelData()
{
	return nullptr;
}

std::pair<size_t, size_t> Image::getCoordinates() const
{
    return std::pair<size_t, size_t>();
}

bool Image::setBounds(Bounds)
{
	return false;
}

std::pair<size_t, size_t> Image::getDimensions() const
{
	return std::pair<size_t, size_t>();
}
