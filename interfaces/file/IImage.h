#pragma once

#include "IFiles.h"
#include "Bounds.h"

class IImage
{
   public:
	IImage()						 = default;
	virtual ~IImage()				 = default;
	IImage(const IImage&)			 = default;
	IImage& operator=(const IImage&) = default;
	IImage(IImage&&)				 = default;
	IImage& operator=(IImage&&)		 = default;

	virtual bool importImage(const bufferStruct& buffer, const imageInfo& image) = 0;
	[[nodiscard]] virtual const char*				getPixelData() const		 = 0;
	[[nodiscard]] virtual std::pair<size_t, size_t> getDimensions() const		 = 0;
	[[nodiscard]] virtual std::pair<size_t, size_t> getCoordinates() const		 = 0;
	virtual bool									setBounds(Bounds)			 = 0;
	virtual bool setResolution(size_t horizontal, size_t vertical)				 = 0;
};