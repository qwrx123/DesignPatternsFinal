#ifndef IDRAWINGENGINE_H
#define IDRAWINGENGINE_H

#include <memory>
#include "IInputManager.h"

class IDrawingTool;
class IStrokeManager;

class IDrawingEngine : public IInputReceiver {
public:
 IDrawingEngine()		   = default;
 virtual ~IDrawingEngine() = default;

 virtual void								  setTool(std::shared_ptr<IDrawingTool> tool) = 0;
 virtual const std::shared_ptr<IDrawingTool>& getActiveTool() const						  = 0;

 virtual const IStrokeManager& getStrokeManager() const = 0;
};

#endif // IDRAWINGENGINE_H