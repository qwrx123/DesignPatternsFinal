#pragma once

#include "IFiles.h"

class ILoad : IFiles
{
   public:
	ILoad()						   = default;
	virtual ~ILoad()			   = default;
	ILoad(const ILoad&)			   = default;
	ILoad& operator=(const ILoad&) = default;
	ILoad(ILoad&&)				   = default;
	ILoad& operator=(ILoad&&)	   = default;

	[[nodiscard]] virtual void loadFile(void*, ssize_t) = 0;
};