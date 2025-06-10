#pragma once

#include "IFiles.h"

class IImport : public IFiles
{
   public:
	IImport()						   = default;
	~IImport() override				   = default;
	IImport(const IImport&)			   = default;
	IImport& operator=(const IImport&) = default;
	IImport(IImport&&)				   = default;
	IImport& operator=(IImport&&)	   = default;

	[[nodiscard]] virtual bool								 importFile()	   = 0;
	[[nodiscard]] virtual std::pair<bufferStruct, imageInfo> getImportedData() = 0;
};