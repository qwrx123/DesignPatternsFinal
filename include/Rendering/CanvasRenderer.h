// CanvasRenderer.h
#ifndef CANVASRENDERER_H
#define CANVASRENDERER_H

#include "ICanvasRenderer.h"
#include "IStroke.h"
#include "IText.h"
#include "Font.h"
#include "Color.h"
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
	void		drawButton(const IButton& button) override;
	void		drawMenu(const IMenu& menu) override;
	void		endFrame() override;

	fileStruct exportCanvas() override;

	static void textRenderTest();
	static void renderGlyph(FT_Face face, FT_GlyphSlot glyph, float x, float y, Color color);

   private:
	GLFWwindow* window_;
	GLuint		textureID_ = 0;	 // Add texture ID for font rendering
};

#endif	// CANVASRENDERER_H