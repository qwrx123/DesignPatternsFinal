#pragma once

#include "IFiles.h"

class IExport : IFiles
{
   public:
	virtual ~IExport() = default;

	[[nodiscard]] virtual void exportFile(void*, ssize_t) = 0;
};