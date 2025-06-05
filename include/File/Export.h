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

	bool					  exportFile(bufferStruct file, imageInfo imageInfo) override;
	[[nodiscard]] std::string quarryFileLocation() override;
	void					  setFileLocation(const std::string& fileLocation) override;
	void					  setFileType(IFiles::type fileType) override;
	void					  setFileName(const std::string& fileName) override;

   private:
	IFiles::type fileType = IFiles::type::bmp;
	std::string	 fileName = "DaisyExport";
	std::string	 fileLocation;

	bool exportTxtFile(bufferStruct file);
	bool exportBmpFile(bufferStruct pixels, imageInfo imageInfo);

	bool setupBmpFileHeader(char* buffer, size_t buffer_size, imageInfo imageInfo);
	bool setupBmpV1Header(char* buffer, size_t buffer_size, imageInfo imageInfo);
	bool setupBmpV5Header(char* buffer, size_t buffer_size, imageInfo imageInfo);
};

#endif	// EXPORT_H