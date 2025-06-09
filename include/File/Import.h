#ifndef IMPORT_H
#define IMPORT_H

#include "IImport.h"

class Import : public IImport
{
   public:
	Import()							 = default;
	~Import() override					 = default;
	Import(const Import&)				 = default;
	Import& operator=(const Import&)	 = default;
	Import(Import&&) noexcept			 = default;
	Import& operator=(Import&&) noexcept = default;

	bool					  importFile(const std::string& fileLocation) override;
	[[nodiscard]] std::string quarryFileLocation() override;
	void					  setFileLocation(const std::string& fileLocation) override;
	void					  setFileType(IFiles::type fileType) override;
	void					  setFileName(const std::string& fileName) override;
};

#endif	// IMPORT_H