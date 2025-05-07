#pragma once

#include "IFiles.h"

class ISave : IFiles
{
   public:
	ISave()			 = default;
	virtual ~ISave() = default;

	virtual void saveFile(void*, ssize_t) = 0;
};