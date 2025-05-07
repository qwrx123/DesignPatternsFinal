#pragma once

#include "IFiles.h"

class IImport : IFiles
{
   public:
	IImport()		   = default;
	virtual ~IImport() = default;

	virtual void importFile(void*, ssize_t) = 0;
};