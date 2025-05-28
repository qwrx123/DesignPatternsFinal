#pragma once

#include "IFiles.h"

class IExport : public IFiles
{
   public:
	IExport()						   = default;
	virtual ~IExport()				   = default;
	IExport(const IExport&)			   = default;
	IExport& operator=(const IExport&) = default;
	IExport(IExport&&)				   = default;
	IExport& operator=(IExport&&)	   = default;

	[[nodiscard]] virtual void exportFile(void*, ssize_t) = 0;
};