#pragma once

#include "IImage.h"
#include "Bounds.h"
#include <memory>

class Image : public IImage
{
   public:
	Image()			  = default;
	~Image() override = default;
	Image(const Image& other);
	Image& operator=(const Image& other);
	Image(Image&&)			  = default;
	Image& operator=(Image&&) = default;

	bool importImage(const bufferStruct& buffer, const imageInfo& image) override;
	[[nodiscard]] const char*				getPixelData() const override;
	[[nodiscard]] std::pair<size_t, size_t> getDimensions() const override;
	[[nodiscard]] std::pair<size_t, size_t> getCoordinates() const override;
	bool									setCoordinates(size_t x, size_t y) override;
	bool setResolution(size_t horizontal, size_t vertical) override;

   private:
	bool setBounds(Bounds imageBounds) override;
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	std::unique_ptr<char[]>	  pixelData	  = nullptr;
	size_t					  width		  = 0;
	size_t					  height	  = 0;
	pixelType				  pixelType	  = pixelType::PIXEL_TYPE_UNKNOWN;
	std::pair<size_t, size_t> coordinates = {0, 0};
	std::pair<size_t, size_t> dimensions  = {0, 0};
	std::pair<size_t, size_t> resolution  = {0, 0};
};