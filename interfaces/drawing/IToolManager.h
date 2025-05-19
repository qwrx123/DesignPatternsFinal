#ifndef ITOOL_MANAGER_H
#define ITOOL_MANAGER_H

#include "IDrawingTool.h"
#include "IStroke.h"

class IToolManager
{
   public:
	virtual ~IToolManager() = default;

	virtual void registerTool(const std::string& name, std::shared_ptr<IDrawingTool> tool) = 0;
	virtual bool selectTool(const std::string& name)									   = 0;

	virtual std::string					  getActiveToolName() const = 0;
	virtual std::shared_ptr<IDrawingTool> getActiveTool() const		= 0;

	virtual void beginStroke(const Point& start) = 0;
	virtual void addPoint(const Point& point)	 = 0;
	virtual void endStroke(const Point& end)	 = 0;
};

#endif	// ITOOL_MANAGER_H