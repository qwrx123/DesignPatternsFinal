#include "ToolManager.h"

ToolManager::ToolManager()
	: current_tool(nullptr), bounds{.top = 0, .bottom = 0, .left = 0, .right = 0}
{
}

ToolManager::~ToolManager() = default;

void ToolManager::registerTool(const std::string& name, std::shared_ptr<IDrawingTool> tool)
{
	bool overwriting_active_tool = (current_tool_name == name);
	tools[name]					 = tool;

	if (overwriting_active_tool)
	{
		current_tool = tool;
	}

	if (!current_tool)
	{
		current_tool	  = tool;
		current_tool_name = name;
	}
}

bool ToolManager::selectTool(const std::string& name)
{
	auto it = tools.find(name);
	if (it != tools.end())
	{
		current_tool	  = it->second;
		current_tool_name = name;
		return true;
	}
	return false;
}

std::string ToolManager::getActiveToolName() const
{
	return current_tool_name;
}

std::shared_ptr<IDrawingTool> ToolManager::getActiveTool() const
{
	return current_tool;
}

void ToolManager::beginStroke(const Point& start)
{
	if (current_tool)
	{
		current_tool->beginStroke(start);
	}
}

void ToolManager::addPoint(const Point& point)
{
	if (current_tool)
	{
		current_tool->addPoint(point);
	}
}

void ToolManager::endStroke(const Point& end)
{
	if (current_tool)
	{
		current_tool->endStroke(end);
	}
}

void ToolManager::setBounds(const Bounds& bounds)
{
	this->bounds = bounds;
}

Bounds ToolManager::getBounds()
{
	return bounds;
}

void ToolManager::onMouseMove(double x, double y)
{
	if (current_tool && current_tool->isDrawing())
	{
		addPoint({.x = x, .y = y});
	}
}

void ToolManager::onMouseButton(MouseButton button, KeyAction action, double x, double y)
{
	if (!current_tool || button != MouseButton::Left)
	{
		return;
	}

	Point p = {.x = x, .y = y};

	if (action == KeyAction::Press && bounds.contains(x, y))
	{
		beginStroke(p);
	}
	else if (action == KeyAction::Release)
	{
		endStroke(p);
	}
}

void ToolManager::onKey(int key, KeyAction action)
{
	// Optional: switch tools with keys
}

void ToolManager::onChar(unsigned int codepoint)
{
	// Optional: handle character input
}

void ToolManager::onResize(int width, int height)
{
	setBounds(Bounds{
		.top = bounds.top, .bottom = (float) height, .left = bounds.left, .right = (float) width});
}

void ToolManager::undoStroke()
{
	current_tool->undoStroke();
}

void ToolManager::redoStroke()
{
	current_tool->redoStroke();
}