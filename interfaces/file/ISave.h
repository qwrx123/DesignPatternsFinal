#pragma once

#include "IFiles.h"

class ISave : IFiles
{
   public:
	ISave()						   = default;
	virtual ~ISave()			   = default;
	ISave(const ISave&)			   = default;
	ISave& operator=(const ISave&) = default;
	ISave(ISave&&)				   = default;
	ISave& operator=(ISave&&)	   = default;

	[[nodiscard]] virtual void saveFile(void*, ssize_t) = 0;
};