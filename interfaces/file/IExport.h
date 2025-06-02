#pragma once

#include "IFiles.h"

class IExport : public IFiles
{
   public:
	IExport()						   = default;
	~IExport() override				   = default;
	IExport(const IExport&)			   = default;
	IExport& operator=(const IExport&) = default;
	IExport(IExport&&)				   = default;
	IExport& operator=(IExport&&)	   = default;

	virtual void exportFile(void*, size_t) = 0;
};