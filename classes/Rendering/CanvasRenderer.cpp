#include "CanvasRenderer.h"
#include <iostream>
#include "Font.h"
#ifdef _WIN32
#include <GL/glext.h>
#endif

CanvasRenderer::CanvasRenderer(GLFWwindow* window) : window_(window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);  // ← Top-left is (0,0)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

CanvasRenderer::~CanvasRenderer() {}

void CanvasRenderer::beginFrame()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
	glClear(GL_COLOR_BUFFER_BIT);
	textRenderTest();
}

void CanvasRenderer::drawStroke(const IStroke& stroke)
{
	const auto& points = stroke.getPoints();
	if (points.size() < 2) return;

	glLineWidth(stroke.getThickness());
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (const auto& p : points)
	{
		glVertex2d(p.x, p.y);
	}
	glEnd();
}

void CanvasRenderer::renderText(const IText& text)
{
	std::string content = text.getContent();
	for (char c : content)
	{
		std::cout << "Rendering character: " << c << std::endl;
	}
}

void CanvasRenderer::drawButton(const IButton& button)
{
	glBegin(GL_QUADS);
	glColor4f(.8, .8, .8, 1);
	glVertex2f(button.getBounds().left, button.getBounds().top);
	glColor4f(.7, .7, .7, 1);
	glVertex2f(button.getBounds().right, button.getBounds().top);
	glColor4f(.3, .3, .3, 1);
	glVertex2f(button.getBounds().right, button.getBounds().bottom);
	glColor4f(.5, .5, .5, 1);
	glVertex2f(button.getBounds().left, button.getBounds().bottom);

	glColor4f(button.getColor().r, button.getColor().g, button.getColor().b, button.getColor().a);
	glVertex2f(button.getBounds().left + 3, button.getBounds().top + 3);
	glVertex2f(button.getBounds().right - 3, button.getBounds().top + 3);
	glVertex2f(button.getBounds().right - 3, button.getBounds().bottom - 3);
	glVertex2f(button.getBounds().left + 3, button.getBounds().bottom - 3);
	glEnd();
}

void CanvasRenderer::drawMenu(const IMenu& menu)
{
	glBegin(GL_QUADS);
	glColor4f(.3, .3, .3, 1);
	glVertex2f(menu.getBounds().left, menu.getBounds().top);
	glVertex2f(menu.getBounds().right, menu.getBounds().top);
	glVertex2f(menu.getBounds().right, menu.getBounds().bottom);
	glVertex2f(menu.getBounds().left, menu.getBounds().bottom);
	glEnd();
}

void CanvasRenderer::renderGlyph(FT_Face face, FT_GlyphSlot glyph, float x, float y)
{
	// Generate texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture parameters - corrected wrapping modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload glyph bitmap as texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyph->bitmap.width, glyph->bitmap.rows, 0, GL_RED,
				 GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

	// Calculate vertex positions
	float x2 = x + glyph->bitmap_left;
	float y2 = y - glyph->bitmap_top;
	float w	 = glyph->bitmap.width;
	float h	 = glyph->bitmap.rows;

	// Enable blending for transparent backgrounds
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set color to white (will be modulated with texture)
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Enable texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Draw textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);  // Changed from (0,0)
	glVertex2f(x2, y2 + h);
	glTexCoord2f(1.0f, 1.0f);  // Changed from (1,0)
	glVertex2f(x2 + w, y2 + h);
	glTexCoord2f(1.0f, 0.0f);  // Changed from (1,1)
	glVertex2f(x2 + w, y2);
	glTexCoord2f(0.0f, 0.0f);  // Changed from (0,1)
	glVertex2f(x2, y2);
	glEnd();

	// Cleanup
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDeleteTextures(1, &texture);
}

void CanvasRenderer::textRenderTest()
{
	std::string text = "Daisy";
	// glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	double x = 100.0f;
	double y = 150.0f;
	glRasterPos2f(x, y);
	std::filesystem::path fontPath = "../include/Delius-Regular.ttf";
	if (!std::filesystem::exists(fontPath))
	{
		return;
	}
	Font font(fontPath);
	for (char c : text)
	{
		if (font.getFontBitmap(c).width == 0)
		{
			std::cerr << "Failed to load glyph for character: " << c << std::endl;
			continue;
		}

		FT_Face face = font.getFontFace();
		renderGlyph(face, face->glyph, x, y);

		// Advance cursor
		x += (face->glyph->advance.x >> 6);	 // Convert from 1/64th pixels to pixels
	}
}

void CanvasRenderer::endFrame()
{
	glfwSwapBuffers(window_);
}

void CanvasRenderer::resize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);  // Top-left origin

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}