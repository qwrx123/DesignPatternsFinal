#ifndef ISTROKEMANAGER_H
#define ISTROKEMANAGER_H

#include <memory>
#include "IStroke.h"

class IStrokeManager
{
   public:
	IStrokeManager()		  = default;
	virtual ~IStrokeManager() = default;

	virtual void addStroke(std::shared_ptr<IStroke> stroke)					= 0;
	virtual const std::vector<std::shared_ptr<IStroke>>& getStrokes() const = 0;
};

#endif	// ISTROKEMANAGER_H