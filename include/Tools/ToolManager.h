#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "IToolManager.h"
#include <unordered_map>

class ToolManager : public IToolManager 
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

private:
    std::unordered_map<std::string, std::shared_ptr<IDrawingTool>> tools;
    std::shared_ptr<IDrawingTool> current_tool;
    std::string current_tool_name;
};

#endif // TOOL_MANAGER_H
