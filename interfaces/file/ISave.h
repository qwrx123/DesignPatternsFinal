#pragma once

#include "IFiles.h"

class ISave : IFiles
{
   public:
	virtual ~ISave() = default;

	[[nodiscard]] virtual void saveFile(void*, ssize_t) = 0;
};