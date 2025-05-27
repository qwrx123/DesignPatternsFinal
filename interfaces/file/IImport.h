#pragma once

#include "IFiles.h"

class IImport : public IFiles
{
   public:
	IImport()						   = default;
	virtual ~IImport()				   = default;
	IImport(const IImport&)			   = default;
	IImport& operator=(const IImport&) = default;
	IImport(IImport&&)				   = default;
	IImport& operator=(IImport&&)	   = default;

	[[nodiscard]] virtual void importFile(void*, ssize_t) = 0;
};