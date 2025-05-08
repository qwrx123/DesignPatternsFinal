#pragma once

#include "IFiles.h"

class IExport : IFiles
{
   public:
	IExport()		   = default;
	virtual ~IExport() = default;

	virtual void exportFile(void*, ssize_t) = 0;
};