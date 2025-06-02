#pragma once

#include <string>
#include <cstdint>

class IFiles
{
   public:
	enum class type : std::uint8_t
	{
		daisy,
		jpg,
		png,
		bmp
	};

	IFiles()						 = default;
	virtual ~IFiles()				 = default;
	IFiles(const IFiles&)			 = default;
	IFiles& operator=(const IFiles&) = default;
	IFiles(IFiles&&)				 = default;
	IFiles& operator=(IFiles&&)		 = default;

	[[nodiscard]] virtual std::string quarryFileLocation()			  = 0;
	virtual void					  setFileType(IFiles::type)		  = 0;
	virtual void					  setFileName(const std::string&) = 0;
};