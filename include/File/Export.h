#ifndef EXPORT_H
#define EXPORT_H

#include "IExport.h"

Class Export : public IExport
{
   public:
	Export()		   = default;
	~Export() override = default;

	Export(const Export& other)				   = default;
	Export& operator=(const Export& other)	   = default;
	Export(Export && other) noexcept		   = default;
	Export& operator=(Export&& other) noexcept = default;

	virtual void					  exportFile(void*, ssize_t);
	[[nodiscard]] virtual std::string quarryFileLocation();
	virtual void					  setFileType(IFiles::type);
}

#endif	// EXPORT_H