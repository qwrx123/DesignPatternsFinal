#pragma once

#include <string>

class IFiles
{
   public:
	enum class type
	{
		daisy,
		jpg,
		png,
		bmp
	};
	virtual std::string quarryFileLocation()	  = 0;
	virtual void		setFileType(IFiles::type) = 0;
};