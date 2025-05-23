// CanvasRenderer.h
#ifndef CANVASRENDERER_H
#define CANVASRENDERER_H

#include "ICanvasRenderer.h"
#include "IStroke.h"
#include "IText.h"
#include "Font.h"
#include <GLFW/glfw3.h>

class CanvasRenderer : public ICanvasRenderer
{
   public:
	CanvasRenderer(GLFWwindow* window);
	~CanvasRenderer() override;

	static void resize(int width, int height);

	void		beginFrame() override;
	void		drawStroke(const IStroke& stroke) override;
	static void renderText(const IText& text);
	void		drawButton(const IButton& button) override;
	void		drawMenu(const IMenu& menu) override;
	void		endFrame() override;

	static void textRenderTest();
	static void renderGlyph(FT_Face face, FT_GlyphSlot glyph, float x, float y);

   private:
	GLFWwindow* window_;
	GLuint		textureID_ = 0;	 // Add texture ID for font rendering
};

#endif	// CANVASRENDERER_H