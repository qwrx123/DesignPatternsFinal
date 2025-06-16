// CanvasRenderer.h
#ifndef CANVASRENDERER_H
#define CANVASRENDERER_H

#include "ICanvasRenderer.h"
#include "IStroke.h"
#include "IText.h"
#include "Font.h"
#include "Color.h"
#include "IImage.h"
#include <GLFW/glfw3.h>

class CanvasRenderer : public ICanvasRenderer
{
   public:
	CanvasRenderer(GLFWwindow* window);
	~CanvasRenderer() override;

	CanvasRenderer(const CanvasRenderer&)			 = delete;
	CanvasRenderer& operator=(const CanvasRenderer&) = delete;
	CanvasRenderer(CanvasRenderer&&)				 = delete;
	CanvasRenderer& operator=(CanvasRenderer&&)		 = delete;

	static void resize(int width, int height);

	void		beginFrame() override;
	void		drawStroke(const IStroke& stroke) override;
	static void renderText(const IText& text);
	void		renderImage(const IImage& image) override;
	void drawButton(const IButton& button, bool renamingLayer = false, int layerBeingRenamed = -1,
					const std::string& renameBuffer = "") override;

	void		drawMenu(const IMenu& menu) override;
	static void drawSliderButton(const IButton& button, float value);
	void		endFrame() override;

	bufferStruct			exportCanvas(Bounds boundingBox = {}) override;
	bool					exportBitmap(std::string fileName, std::string fileLocation,
										 Bounds boundingBox = {}) override;
	std::pair<float, float> getWindowDPI() override;

	static void textRenderTest();
	static void renderGlyph(FT_Face face, FT_GlyphSlot glyph, float x, float y, Color color);
	static void renderLabel(const std::string& label, float x, float y, Color color);

   private:
	GLFWwindow* window_;
	GLuint		textureID_ = 0;	 // Add texture ID for font rendering
};

#endif	// CANVASRENDERER_H