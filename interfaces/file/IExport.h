#pragma once

#include "IFiles.h"
#include <memory>

class IExport : public IFiles
{
   public:
	IExport()						   = default;
	~IExport() override				   = default;
	IExport(const IExport&)			   = default;
	IExport& operator=(const IExport&) = default;
	IExport(IExport&&)				   = default;
	IExport& operator=(IExport&&)	   = default;

	virtual bool exportFile(fileStruct, imageInfo) = 0;
};