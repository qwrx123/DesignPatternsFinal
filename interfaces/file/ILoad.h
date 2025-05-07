#pragma once

#include "IFiles.h"

class ILoad : IFiles
{
   public:
	ILoad()			 = default;
	virtual ~ILoad() = default;

	virtual void loadFile(void*, ssize_t) = 0;
};