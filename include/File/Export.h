#ifndef EXPORT_H
#define EXPORT_H

#include "IExport.h"

class Export : public IExport
{
   public:
	Export()		   = default;
	~Export() override = default;

	Export(const Export& other)				   = default;
	Export& operator=(const Export& other)	   = default;
	Export(Export&& other) noexcept			   = default;
	Export& operator=(Export&& other) noexcept = default;

	void					  exportFile(void* fileLocation, size_t fileSize) override;
	[[nodiscard]] std::string quarryFileLocation() override;
	void					  setFileType(IFiles::type fileType) override;
};

#endif	// EXPORT_H