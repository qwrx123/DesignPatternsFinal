#pragma once

#include <string>

class IFiles
{
   public:
	virtual std::string quarryFileLocation() = 0;
};