#include "CanvasRenderer.h"
#include <iostream>
#include "Font.h"
#ifdef _WIN32
#include <GL/glext.h>
#endif

CanvasRenderer::CanvasRenderer(GLFWwindow* window) : window_(window)
{
	int width  = 0;
	int height = 0;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int right  = width;
	int bottom = height;
	glOrtho(0, right, bottom, 0, -1, 1);  // ← Top-left is (0,0)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

CanvasRenderer::~CanvasRenderer() = default;

void CanvasRenderer::beginFrame()
{
	glClearColor(1.0F, 1.0F, 1.0F, 1.0F);  // White background
	glClear(GL_COLOR_BUFFER_BIT);
	textRenderTest();
}

void CanvasRenderer::drawStroke(const IStroke& stroke)
{
	const auto& points = stroke.getPoints();
	if (points.size() < 2)
	{
		return;
	}

	glLineWidth(stroke.getThickness());
	glColor4f(stroke.getColor().r, stroke.getColor().g, stroke.getColor().b, stroke.getColor().a);
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
		std::cout << "Rendering character: " << c << "\n";
	}
}

void CanvasRenderer::drawButton(const IButton& button)
{
	static const float lighterGray = 0.8F;
	static const float lightGray   = 0.7F;
	static const float gray		   = 0.5F;
	static const float darkGray	   = 0.3F;

	glBegin(GL_QUADS);
	glColor4f(lighterGray, lighterGray, lighterGray, 1);
	glVertex2f(button.getBounds().left, button.getBounds().top);
	glColor4f(lightGray, lightGray, lightGray, 1);
	glVertex2f(button.getBounds().right, button.getBounds().top);
	glColor4f(darkGray, darkGray, darkGray, 1);
	glVertex2f(button.getBounds().right, button.getBounds().bottom);
	glColor4f(gray, gray, gray, 1);
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
	static const float darkGray = 0.3F;

	glBegin(GL_QUADS);
	glColor4f(darkGray, darkGray, darkGray, 1);
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

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture parameters - corrected wrapping modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload glyph bitmap as texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, static_cast<GLsizei>(glyph->bitmap.width),
				 static_cast<GLsizei>(glyph->bitmap.rows), 0, GL_RED, GL_UNSIGNED_BYTE,
				 glyph->bitmap.buffer);

	// Calculate vertex positions
	float x2 = x + static_cast<float>(glyph->bitmap_left);
	float y2 = y - static_cast<float>(glyph->bitmap_top);
	auto  w	 = static_cast<float>(glyph->bitmap.width);
	auto  h	 = static_cast<float>(glyph->bitmap.rows);

	// Enable blending for transparent backgrounds
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set color to white (will be modulated with texture)
	glColor4f(1.0F, 1.0F, 1.0F, 1.0F);

	// Enable texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Draw textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0F, 1.0F);  // Changed from (0,0)
	glVertex2f(x2, y2 + h);
	glTexCoord2f(1.0F, 1.0F);  // Changed from (1,0)
	glVertex2f(x2 + w, y2 + h);
	glTexCoord2f(1.0F, 0.0F);  // Changed from (1,1)
	glVertex2f(x2 + w, y2);
	glTexCoord2f(0.0F, 0.0F);  // Changed from (0,1)
	glVertex2f(x2, y2);
	glEnd();

	// Cleanup
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDeleteTextures(1, &texture);
}

void CanvasRenderer::textRenderTest()
{
	std::string text	 = "Daisy";
	const float defaultX = 100.0F;
	const float defaultY = 150.0F;
	// glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	float x = defaultX;
	float y = defaultY;
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
			std::cerr << "Failed to load glyph for character: " << c << "\n";
			continue;
		}

		FT_Face face = font.getFontFace();
		renderGlyph(face, face->glyph, x, y);

		const int pixelShift = 6;
		// Advance cursor
		x += static_cast<float>(face->glyph->advance.x >> pixelShift);
		// Convert from 1/64th pixels to pixels
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
	int right  = width;
	int bottom = height;
	glOrtho(0, right, bottom, 0, -1, 1);  // Top-left origin

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}