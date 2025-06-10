#ifndef ISTROKEMANAGER_H
#define ISTROKEMANAGER_H

#include <memory>
#include <vector>
#include "IStroke.h"

class IStrokeManager
{
   public:
	IStrokeManager()								 = default;
	virtual ~IStrokeManager()						 = default;
	IStrokeManager(const IStrokeManager&)			 = default;
	IStrokeManager& operator=(const IStrokeManager&) = default;
	IStrokeManager(IStrokeManager&&)				 = default;
	IStrokeManager& operator=(IStrokeManager&&)		 = default;

	virtual void addStroke(std::shared_ptr<IStroke> stroke)								  = 0;
	[[nodiscard]] virtual const std::vector<std::shared_ptr<IStroke>>& getStrokes() const = 0;
	virtual void													   clear()			  = 0;
	virtual void splitEraseWithPath(const std::shared_ptr<IStroke>& eraser_path,
									float							eraser_radius)								  = 0;
	virtual void removeLastStroke()														  = 0;
};

#endif	// ISTROKEMANAGER_H