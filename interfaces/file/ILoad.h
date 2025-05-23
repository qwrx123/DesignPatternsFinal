#pragma once

#include "IFiles.h"

class ILoad : IFiles
{
   public:
	virtual ~ILoad() = default;

	[[nodiscard]] virtual void loadFile(void*, ssize_t) = 0;
};