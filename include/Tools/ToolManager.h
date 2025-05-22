#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "IToolManager.h"
#include "IInputReceiver.h"
#include <unordered_map>

class ToolManager : public IToolManager, public IInputReceiver 
{
public:
    ToolManager();
	~ToolManager();

	void registerTool(const std::string& name, std::shared_ptr<IDrawingTool> tool) override;
    bool selectTool(const std::string& name) override;

    std::string getActiveToolName() const override;
    std::shared_ptr<IDrawingTool> getActiveTool() const override;

    void beginStroke(const Point& start) override;
    void addPoint(const Point& point) override;
    void endStroke(const Point& end) override;

    void onMouseMove(double x, double y) override;
    void onMouseButton(MouseButton button, KeyAction action, double x, double y) override;
    void onKey(int key, KeyAction action) override;
    void onChar(unsigned int codepoint) override;

private:
    std::unordered_map<std::string, std::shared_ptr<IDrawingTool>> tools;
    std::shared_ptr<IDrawingTool> current_tool;
    std::string current_tool_name;
};

#endif // TOOL_MANAGER_H
