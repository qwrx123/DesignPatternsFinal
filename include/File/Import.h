#ifndef IMPORT_H
#define IMPORT_H

#include "IImport.h"

class Import : public IImport
{
   public:
	Import()							 = default;
	~Import() override					 = default;
	Import(const Import&)				 = delete;
	Import& operator=(const Import&)	 = delete;
	Import(Import&&) noexcept			 = default;
	Import& operator=(Import&&) noexcept = default;

	bool											 importFile() override;
	[[nodiscard]] std::pair<bufferStruct, imageInfo> getImportedData() override;
	[[nodiscard]] std::string						 quarryFileLocation() override;
	void setFileLocation(const std::string& fileLocation) override;
	void setFileType(IFiles::type fileType) override;
	void setFileName(const std::string& fileName) override;
	bool setBuffer(bufferStruct buffer);
	bool setImageInfo(imageInfo info);

   private:
	bool readTxtFile();

	IFiles::type fileType = IFiles::type::bmp;
	std::string	 fileName = "DaisyExport";
	std::string	 fileLocation;

	bufferStruct importedBuffer	   = {};
	imageInfo	 importedImageInfo = {};
};

#endif	// IMPORT_H