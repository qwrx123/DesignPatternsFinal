#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "IToolManager.h"
#include "IInputReceiver.h"
#include <unordered_map>

class ToolManager : public IToolManager, public IInputReceiver
{
   public:
	ToolManager();
	~ToolManager() override;

	ToolManager(const ToolManager&)			   = default;
	ToolManager& operator=(const ToolManager&) = default;
	ToolManager(ToolManager&&) noexcept		   = default;
	ToolManager& operator=(ToolManager&&)	   = default;

	void registerTool(const std::string& name, std::shared_ptr<IDrawingTool> tool) override;
	bool selectTool(const std::string& name) override;

	[[nodiscard]] std::string					getActiveToolName() const override;
	[[nodiscard]] std::shared_ptr<IDrawingTool> getActiveTool() const override;

	void beginStroke(const Point& start) override;
	void addPoint(const Point& point) override;
	void endStroke(const Point& end) override;

	void				 setBounds(const Bounds& bounds) override;
	[[nodiscard]] Bounds getBounds() override;

	void onMouseMove(double x, double y) override;
	void onMouseButton(MouseButton button, KeyAction action, double x, double y) override;
	void onKey(int key, KeyAction action) override;
	void onChar(unsigned int codepoint) override;
	void onResize(int width, int height) override;

	void undoStroke() override;
	void redoStroke() override;
	void clearStrokes() override;

   private:
	std::unordered_map<std::string, std::shared_ptr<IDrawingTool>> tools;
	std::shared_ptr<IDrawingTool>								   current_tool;
	std::string													   current_tool_name;
	Bounds														   bounds;
};

#endif	// TOOL_MANAGER_H
