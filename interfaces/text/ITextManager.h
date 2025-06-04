#ifndef ITEXTMANAGER_H
#define ITEXTMANAGER_H

#include <memory>
#include <vector>
#include "IText.h"

class ITextManager
{
   public:
	ITextManager()								 = default;
	virtual ~ITextManager()						 = default;
	ITextManager(const ITextManager&)			 = default;
	ITextManager& operator=(const ITextManager&) = default;
	ITextManager(ITextManager&&)				 = default;
	ITextManager& operator=(ITextManager&&)		 = default;

	virtual void addText(std::shared_ptr<IText> text)	 = 0;
	virtual void removeText(std::shared_ptr<IText> text) = 0;

	virtual void			   registerTextTool(std::shared_ptr<IText> text) = 0;
	[[nodiscard]] virtual bool isTextToolActive() const						 = 0;
	virtual void			   setTextToolActive()							 = 0;
	virtual void			   setTextToolInactive()						 = 0;

	[[nodiscard]] virtual const std::vector<std::shared_ptr<IText>>& getTexts() const = 0;

	[[nodiscard]] virtual std::shared_ptr<IText> getTextAt(double x, double y) const = 0;
	virtual void								 clearAll()							 = 0;
	virtual void								 setFontSize(int size)				 = 0;
};

#endif	// ITEXTMANAGER_H
