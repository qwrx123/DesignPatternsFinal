#ifndef EXPORT_H
#define EXPORT_H

#include "IExport.h"
#include <memory>

class Export : public IExport
{
   public:
	Export()		   = default;
	~Export() override = default;

	Export(const Export& other)				   = default;
	Export& operator=(const Export& other)	   = default;
	Export(Export&& other) noexcept			   = default;
	Export& operator=(Export&& other) noexcept = default;

	bool					  exportFile(fileStruct file) override;
	[[nodiscard]] std::string quarryFileLocation() override;
	void					  setFileLocation(const std::string& fileLocation) override;
	void					  setFileType(IFiles::type fileType) override;
	void					  setFileName(const std::string& fileName) override;

   private:
	IFiles::type fileType = IFiles::type::bmp;
	std::string	 fileName = "DaisyExport";
	std::string	 fileLocation;
};

#endif	// EXPORT_H