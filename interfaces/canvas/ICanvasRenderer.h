// ICanvasRenderer.h
#ifndef ICANVASRENDERER_H
#define ICANVASRENDERER_H

#include <vector>
#include "IStroke.h"
#include "IButton.h"
#include "IMenu.h"
#include "IFiles.h"

class ICanvasRenderer
{
   public:
	ICanvasRenderer()								   = default;
	virtual ~ICanvasRenderer()						   = default;
	ICanvasRenderer(const ICanvasRenderer&)			   = default;
	ICanvasRenderer& operator=(const ICanvasRenderer&) = default;
	ICanvasRenderer(ICanvasRenderer&&)				   = default;
	ICanvasRenderer& operator=(ICanvasRenderer&&)	   = default;

	virtual bufferStruct exportCanvas()												  = 0;
	virtual bool		 exportBitmap(std::string fileName, std::string fileLocation) = 0;
	virtual std::pair<float, float> getWindowDPI()									  = 0;

	// Called once per frame
	virtual void beginFrame()					   = 0;
	virtual void drawStroke(const IStroke& stroke) = 0;
	virtual void drawButton(const IButton& button) = 0;
	virtual void drawMenu(const IMenu& menu)	   = 0;
	virtual void endFrame()						   = 0;
};

#endif	// ICANVASRENDERER_H