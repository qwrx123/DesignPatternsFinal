#include "ToolManager.h"

ToolManager::ToolManager()
    : current_tool(nullptr), current_tool_name("") {}

ToolManager::~ToolManager() = default;

void ToolManager::registerTool(const std::string& name, std::shared_ptr<IDrawingTool> tool) {
    tools[name] = tool;

    // Optionally auto-select the first registered tool
    if (!current_tool) {
        current_tool = tool;
        current_tool_name = name;
    }
}

bool ToolManager::selectTool(const std::string& name) {
    auto it = tools.find(name);
    if (it != tools.end()) {
        current_tool = it->second;
        current_tool_name = name;
        return true;
    }
    return false;
}

std::string ToolManager::getActiveToolName() const {
    return current_tool_name;
}

std::shared_ptr<IDrawingTool> ToolManager::getActiveTool() const {
    return current_tool;
}

void ToolManager::beginStroke(const Point& start) {
    if (current_tool) {
        current_tool->beginStroke(start);
    }
}

void ToolManager::addPoint(const Point& point) {
    if (current_tool) {
        current_tool->addPoint(point);
    }
}

void ToolManager::endStroke(const Point& end) {
    if (current_tool) {
        current_tool->endStroke(end);
    }
}

void ToolManager::onMouseMove(double x, double y) {
    if (current_tool && current_tool->isDrawing()) {
        addPoint({x, y});
    }
}

void ToolManager::onMouseButton(MouseButton button, KeyAction action, double x, double y) {
    if (!current_tool || button != MouseButton::Left) return;

    Point p = {x, y};

    if (action == KeyAction::Press) {
        beginStroke(p);
    } else if (action == KeyAction::Release) {
        endStroke(p);
    }
}

void ToolManager::onKey(int key, KeyAction action) {
    // Optional: switch tools with keys
    // Example:
    // if (action == KeyAction::Press && key == GLFW_KEY_E) selectTool("eraser");
}

void ToolManager::onChar(unsigned int codepoint) {
    // Optional: handle character input
    // Example: if (codepoint == 'B') selectTool("brush");
}
