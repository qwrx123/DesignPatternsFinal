// ICanvasRenderer.h
#ifndef ICANVASRENDERER_H
#define ICANVASRENDERER_H

#include <vector>
#include "IStroke.h"

class ICanvasRenderer
{
   public:
	virtual ~ICanvasRenderer() = default;

	// Called once per frame
	virtual void beginFrame()					   = 0;
	virtual void drawStroke(const IStroke& stroke) = 0;
	virtual void endFrame()						   = 0;
};

#endif	// ICANVASRENDERER_H