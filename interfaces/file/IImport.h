#pragma once

#include "IFiles.h"

class IImport : IFiles
{
   public:
	virtual ~IImport() = default;

	[[nodiscard]] virtual void importFile(void*, ssize_t) = 0;
};