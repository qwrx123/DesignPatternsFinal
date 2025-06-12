#pragma once

#include "IImage.h"
#include "Bounds.h"
#include <memory>

class Image : public IImage
{
   public:
	Image()							= default;
	virtual ~Image()				= default;
	Image(const IImage&)			= default;
	Image& operator=(const IImage&) = default;
	Image(IImage&&)					= default;
	Image& operator=(IImage&&)		= default;

	bool			  importImage(const bufferStruct& buffer, const imageInfo& image) override;
	const char* const getPixelData() const override;
	std::pair<size_t, size_t> getDimensions() const override;
	std::pair<size_t, size_t> getCoordinates() const override;
	bool					  setBounds(Bounds) override;
	bool					  setResolution(size_t horizontal, size_t vertical) override;

   private:
	std::unique_ptr<char[]>	  pixelData	  = nullptr;
	size_t					  width		  = 0;
	size_t					  height	  = 0;
	pixelType				  pixelType	  = pixelType::PIXEL_TYPE_UNKNOWN;
	std::pair<size_t, size_t> coordinates = {0, 0};
	std::pair<size_t, size_t> dimensions  = {0, 0};
	std::pair<size_t, size_t> resolution  = {0, 0};
}