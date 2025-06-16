#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CanvasRenderer.h"
#include "InputManager.h"
#include "ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "MenuBar.h"
#include "ButtonClass.h"
#include "TextManager.h"
#include "LayerManager.h"

const int		  defaultWindowWidth  = 800;
const int		  defaultWindowHeight = 600;
const char* const defaultWindowTitle  = "Drawing App";

const float defaultEraserSize	 = 10.0F;
const float defaultThickness	 = 2.0F;
const int	defaultMenuBarHeight = 100;
const int	defaultFontSize		 = 48;

GLFWwindow* initializeWindow()
{
	if (glfwInit() == GLFW_FALSE)
	{
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(defaultWindowWidth, defaultWindowHeight,
										  defaultWindowTitle, nullptr, nullptr);
	if (!(bool) window)
	{
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return nullptr;
	}
	return window;
}

void initializeObjects(GLFWwindow* window, std::unique_ptr<CanvasRenderer>& renderer,
					   std::shared_ptr<LayerManager>&  layerManager,
					   std::shared_ptr<StrokeManager>& strokeManager,
					   std::shared_ptr<ToolManager>&   toolManager,
					   std::shared_ptr<InputManager>&  inputManager,
					   std::shared_ptr<MenuBar>& menuBar, std::shared_ptr<TextManager>& textManager)
{
	renderer	  = std::make_unique<CanvasRenderer>(window);
	layerManager  = std::make_shared<LayerManager>();
	strokeManager = std::make_shared<StrokeManager>(layerManager);
	toolManager	  = std::make_shared<ToolManager>();
	inputManager  = std::make_shared<InputManager>();
	menuBar		  = std::make_shared<MenuBar>();
	textManager	  = std::make_shared<TextManager>();

	inputManager->bindToWindow(window);
	inputManager->registerReceiver(toolManager);
	inputManager->registerReceiver(menuBar);
	inputManager->registerReceiver(textManager);
	inputManager->setResizeCallback([&](int w, int h) { CanvasRenderer::resize(w, h); });

	toolManager->setBounds({.top	= defaultMenuBarHeight,
							.bottom = defaultWindowHeight,
							.left	= 0,
							.right	= defaultWindowWidth});
	toolManager->registerTool(
		"Brush", std::make_shared<BrushTool>(layerManager, strokeManager,
											 Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F},
											 defaultThickness));
	toolManager->registerTool(
		"Eraser", std::make_shared<EraserTool>(layerManager, strokeManager, defaultEraserSize));

	textManager->registerTextTool(std::make_shared<Text>(
		"",
		Bounds(defaultFontSize + defaultMenuBarHeight, defaultWindowHeight, 0, defaultWindowWidth),
		"Delius", defaultFontSize, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, true));

	menuBar->setBounds(
		{.top = 0, .bottom = defaultMenuBarHeight, .left = 0, .right = defaultWindowWidth});
	menuBar->setToolPointer(toolManager);
	menuBar->setTextPointer(textManager);
	menuBar->setLayerPointer(layerManager);
	menuBar->setDefaultButtons();
}

void renderFrame(CanvasRenderer& renderer, LayerManager& layerManager, ToolManager& toolManager,
				 TextManager& textManager, MenuBar& menuBar)
{
	renderer.beginFrame();

	for (const auto& layer : layerManager.getAllLayers())
	{
		for (const auto& stroke : layer->getStrokes())
		{
			renderer.drawStroke(*stroke);
		}
	}

	for (const auto& text : textManager.getTexts())
	{
		CanvasRenderer::renderText(*text);
	}

	if (toolManager.getActiveToolName() == "Brush")
	{
		auto brush		 = std::dynamic_pointer_cast<BrushTool>(toolManager.getActiveTool());
		auto live_stroke = brush->getCurrentStroke();
		if (live_stroke && live_stroke->getPoints().size() >= 2)
		{
			renderer.drawStroke(*live_stroke);
		}
	}

	renderer.drawMenu(menuBar);

	for (const auto& button : menuBar.getButtons())
	{
		if (button->getLabel() == "size" || button->getLabel() == "red" ||
			button->getLabel() == "green" || button->getLabel() == "blue" ||
			button->getLabel() == "opacity")
		{
			CanvasRenderer::drawSliderButton(*button, button->getValue());
		}
		else
		{
			renderer.drawButton(*button);
		}
	}

	menuBar.update();

	for (size_t i = 0; i < menuBar.getLayerDropdownButtons().size(); ++i)
	{
		const auto& dropdown = menuBar.getLayerDropdownButtons()[i];
		bool isBeingRenamed	 = menuBar.isRenaming() && ((int) i == menuBar.getLayerBeingRenamed());
		std::string renameBuffer = isBeingRenamed ? menuBar.getRenameBuffer() : "";

		renderer.drawButton(*dropdown, isBeingRenamed, 0, renameBuffer);
	}

	for (const auto& del : menuBar.getLayerDeleteButtons())
	{
		renderer.drawButton(*del);
	}

	renderer.endFrame();
}

void mainLoop(GLFWwindow* window, CanvasRenderer& renderer, LayerManager& layerManager,
			  ToolManager& toolManager, TextManager& textManager, MenuBar& menuBar,
			  InputManager& inputManager)
{
	while (!(bool) glfwWindowShouldClose(window))
	{
		inputManager.beginFrame();
		glfwPollEvents();

		renderFrame(renderer, layerManager, toolManager, textManager, menuBar);

		inputManager.endFrame();
	}
}

int main()
{
	GLFWwindow* window = initializeWindow();
	if (!(bool) window)
	{
		return -1;
	}

	std::unique_ptr<CanvasRenderer> renderer;
	std::shared_ptr<LayerManager>	layerManager;
	std::shared_ptr<StrokeManager>	strokeManager;
	std::shared_ptr<ToolManager>	toolManager;
	std::shared_ptr<InputManager>	inputManager;
	std::shared_ptr<MenuBar>		menuBar;
	std::shared_ptr<TextManager>	textManager;

	initializeObjects(window, renderer, layerManager, strokeManager, toolManager, inputManager,
					  menuBar, textManager);
	mainLoop(window, *renderer, *layerManager, *toolManager, *textManager, *menuBar, *inputManager);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}