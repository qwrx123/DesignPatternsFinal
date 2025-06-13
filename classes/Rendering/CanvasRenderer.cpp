#include "CanvasRenderer.h"
#include "Font.h"
#include "Color.h"
#include <iostream>
#include <cstring>
#include <vector>
#include "Export.h"
#include "Text.h"
#include "SliderButton.h"
#include <utility>
#ifdef _WIN32
#include <GL/glext.h>
#endif

static const Color lighterGray			= {.r = 0.8F, .g = 0.8F, .b = 0.8F, .a = 1.0F};
static const Color lightGray			= {.r = 0.7F, .g = 0.7F, .b = 0.7F, .a = 1.0F};
static const Color gray					= {.r = 0.5F, .g = 0.5F, .b = 0.5F, .a = 1.0F};
static const Color darkGray				= {.r = 0.3F, .g = 0.3F, .b = 0.3F, .a = 1.0F};
static const Color sliderColor			= {.r = 0.0F, .g = 0.5F, .b = 1.0F, .a = 1.0F};
static const int   labelSize			= 14;
static const float labelCenteringFactor = 4.0F;
static const float buttonLabelYOffset	= 5.0F;
static const int   halfSliderWidth		= 5;
static const int   buttonBorder			= 3;

CanvasRenderer::CanvasRenderer(GLFWwindow* window) : window_(window)
{
	int width  = 0;
	int height = 0;
	glfwGetFramebufferSize(window_, &width, &height);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int right  = width;
	int bottom = height;
	glOrtho(0, right, bottom, 0, -1, 1);

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
	glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CanvasRenderer::drawStroke(const IStroke& stroke)
{
	const auto& points = stroke.getPoints();
	if (points.size() < 2)
	{
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Color color = stroke.getColor();
	glColor4f(color.r, color.g, color.b, color.a);

	glLineWidth(stroke.getThickness());
	glBegin(GL_LINE_STRIP);
	for (const auto& p : points)
	{
		glVertex2f(static_cast<float>(p.x), static_cast<float>(p.y));
	}
	glEnd();

	glDisable(GL_BLEND);
}

void CanvasRenderer::drawButton(const IButton& button)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glColor4f(lighterGray.r, lighterGray.g, lighterGray.b, lighterGray.a);
	glVertex2f(button.getBounds().left, button.getBounds().top);
	glColor4f(lightGray.r, lightGray.g, lightGray.b, lightGray.a);
	glVertex2f(button.getBounds().right, button.getBounds().top);
	glColor4f(darkGray.r, darkGray.g, darkGray.b, darkGray.a);
	glVertex2f(button.getBounds().right, button.getBounds().bottom);
	glColor4f(gray.r, gray.g, gray.b, gray.a);
	glVertex2f(button.getBounds().left, button.getBounds().bottom);

	glColor4f(button.getColor().r, button.getColor().g, button.getColor().b, button.getColor().a);
	glVertex2f(button.getBounds().left + buttonBorder, button.getBounds().top + buttonBorder);
	glVertex2f(button.getBounds().right - buttonBorder, button.getBounds().top + buttonBorder);
	glVertex2f(button.getBounds().right - buttonBorder, button.getBounds().bottom - buttonBorder);
	glVertex2f(button.getBounds().left + buttonBorder, button.getBounds().bottom - buttonBorder);
	glEnd();

	glDisable(GL_BLEND);
}

void CanvasRenderer::drawMenu(const IMenu& menu)
{
	glBegin(GL_QUADS);
	glColor4f(darkGray.r, darkGray.g, darkGray.b, darkGray.a);
	glVertex2f(menu.getBounds().left, menu.getBounds().top);
	glVertex2f(menu.getBounds().right, menu.getBounds().top);
	glVertex2f(menu.getBounds().right, menu.getBounds().bottom);
	glVertex2f(menu.getBounds().left, menu.getBounds().bottom);
	glEnd();
}

void CanvasRenderer::renderText(const IText& text)
{
	std::string			  content  = text.getContent();
	int					  fontSize = text.getFontSize();
	Color				  color	   = text.getColor();
	float				  x		   = text.getBounds().left;
	float				  y		   = text.getBounds().top;
	std::filesystem::path fontPath = "../include/Delius-Regular.ttf";
	if (!std::filesystem::exists(fontPath))
	{
		return;
	}
	Font font(fontPath);
	font.setFontSize(fontSize);
	const int pixleConversionFactor = 6;
	for (char c : content)
	{
		if (font.getFontBitmap(c).width == 0 && c != ' ' && c != '\t')
		{
			std::cout << "Failed to load glyph for character: " << c << "\n";
			continue;
		}
		FT_Face face = font.getFontFace();

		renderGlyph(face, face->glyph, x, y, color);
		x += static_cast<float>(face->glyph->advance.x >> pixleConversionFactor);
	}
}

void CanvasRenderer::renderGlyph(FT_Face face, FT_GlyphSlot glyph, float x, float y, Color color)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, static_cast<GLsizei>(glyph->bitmap.width),
				 static_cast<GLsizei>(glyph->bitmap.rows), 0, GL_ALPHA, GL_UNSIGNED_BYTE,
				 glyph->bitmap.buffer);

	float x2 = x + static_cast<float>(glyph->bitmap_left);
	float y2 = y - static_cast<float>(glyph->bitmap_top);
	auto  w	 = static_cast<float>(glyph->bitmap.width);
	auto  h	 = static_cast<float>(glyph->bitmap.rows);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(color.r, color.g, color.b, color.a);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0F, 1.0F);
	glVertex2f(x2, y2 + h);
	glTexCoord2f(1.0F, 1.0F);
	glVertex2f(x2 + w, y2 + h);
	glTexCoord2f(1.0F, 0.0F);
	glVertex2f(x2 + w, y2);
	glTexCoord2f(0.0F, 0.0F);
	glVertex2f(x2, y2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDeleteTextures(1, &texture);
}

void CanvasRenderer::drawSliderButton(const IButton& button, float value)
{
	glBegin(GL_QUADS);
	glColor4f(lighterGray.r, lighterGray.g, lighterGray.b, lighterGray.a);
	glVertex2f(button.getBounds().left, button.getBounds().top);
	glColor4f(lightGray.r, lightGray.g, lightGray.b, lightGray.a);
	glVertex2f(button.getBounds().right, button.getBounds().top);
	glColor4f(darkGray.r, darkGray.g, darkGray.b, darkGray.a);
	glVertex2f(button.getBounds().right, button.getBounds().bottom);
	glColor4f(gray.r, gray.g, gray.b, gray.a);
	glVertex2f(button.getBounds().left, button.getBounds().bottom);

	glVertex2f(button.getBounds().left + buttonBorder, button.getBounds().top + buttonBorder);
	glVertex2f(button.getBounds().left + buttonBorder, button.getBounds().bottom - buttonBorder);
	glColor4f(button.getColor().r, button.getColor().g, button.getColor().b, button.getColor().a);
	glVertex2f(button.getBounds().right - buttonBorder, button.getBounds().bottom - buttonBorder);
	glVertex2f(button.getBounds().right - buttonBorder, button.getBounds().top + buttonBorder);

	float sliderPosition = (button.getBounds().left +
							((button.getBounds().right - (button.getBounds().left)) * value));
	glColor4f(sliderColor.r, sliderColor.g, sliderColor.b, sliderColor.a);
	glVertex2f(sliderPosition - halfSliderWidth, button.getBounds().top + buttonBorder);
	glVertex2f(sliderPosition + halfSliderWidth, button.getBounds().top + buttonBorder);
	glVertex2f(sliderPosition + halfSliderWidth, button.getBounds().bottom - buttonBorder);
	glVertex2f(sliderPosition - halfSliderWidth, button.getBounds().bottom - buttonBorder);

	int			newValue = static_cast<int>(value * 100.0F);
	std::string valueStr = " " + std::to_string(newValue);
	float		textX =
		button.getBounds().left + ((button.getBounds().right - button.getBounds().left) / 2);
	float textY = button.getBounds().top +
				  ((button.getBounds().bottom - button.getBounds().top) / 2) + buttonLabelYOffset;
	textX -= static_cast<float>(valueStr.length() * labelSize) / labelCenteringFactor;
	renderLabel(valueStr, textX, textY, Color{.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 1.0F});
	glEnd();
}

void CanvasRenderer::renderLabel(const std::string& label, float x, float y, Color color)
{
	std::filesystem::path fontPath = "../include/Delius-Regular.ttf";
	if (!std::filesystem::exists(fontPath))
	{
		return;
	}
	Font font(fontPath);
	font.setFontSize(labelSize);
	const int pixleConversionFactor = 6;
	for (char c : label)
	{
		if (font.getFontBitmap(c).width == 0 && c != ' ' && c != '\t')
		{
			std::cout << "Failed to load glyph for character: " << c << "\n";
			continue;
		}
		FT_Face face = font.getFontFace();

		renderGlyph(face, face->glyph, x, y, color);
		x += static_cast<float>(face->glyph->advance.x >> pixleConversionFactor);
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
	glOrtho(0, right, bottom, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bufferStruct CanvasRenderer::exportCanvas()
{
	bufferStruct canvasBuffer;

	int width  = 0;
	int height = 0;
	glfwGetFramebufferSize(window_, &width, &height);

	// RGBA format size
	canvasBuffer.bufferSize = static_cast<size_t>(width) * static_cast<size_t>(height) * 4;

	// Proper way to allocate memory for the buffer safely
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
	canvasBuffer.bufferLocation = std::make_unique<char[]>(canvasBuffer.bufferSize);

	char*		 pixelData = canvasBuffer.bufferLocation.get();
	const size_t pixelSize = 4;

	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
#ifdef _WIN32
	glReadBuffer(GL_FRONT);
#else
	glReadBuffer(GL_BACK);
#endif
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, canvasBuffer.bufferLocation.get());

	std::vector<char> scanLine(width * pixelSize);
	char*			  scanLineBuff = scanLine.data();
	// Flip the image vertically
	for (size_t y = 0; y < static_cast<size_t>(height) / 2; ++y)
	{
		size_t topRowOffset	   = y * width * pixelSize;
		size_t bottomRowOffset = (height - 1 - y) * width * pixelSize;

		// Working with raw memory means we need to be careful with pointer arithmetic
		// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
		std::memcpy(scanLineBuff, pixelData + topRowOffset, width * pixelSize);
		std::memcpy(pixelData + topRowOffset, pixelData + bottomRowOffset, width * pixelSize);
		std::memcpy(pixelData + bottomRowOffset, scanLineBuff, width * pixelSize);
		// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	}

	return std::move(canvasBuffer);
}

bool CanvasRenderer::exportBitmap(std::string fileName, std::string fileLocation)
{
	bufferStruct canvasBuffer = exportCanvas();

	if (!canvasBuffer.bufferLocation || canvasBuffer.bufferSize == 0)
	{
		return false;
	}

	imageInfo imageInfo;

	int width  = 0;
	int height = 0;
	glfwGetFramebufferSize(window_, &width, &height);

	imageInfo.width	 = width;
	imageInfo.height = height;

	const float inchToM = 39.37F;

	std::pair<float, float> dpi	   = getWindowDPI();
	imageInfo.horizontalResolution = static_cast<size_t>(dpi.first * inchToM);
	imageInfo.verticalResolution   = static_cast<size_t>(dpi.second * inchToM);
	imageInfo.pixelType			   = pixelType::PIXEL_TYPE_RGBA;

	Export exportFile;
	if (fileLocation.empty())
	{
		fileLocation = exportFile.quarryFileLocation();
	}
	if (fileName.empty())
	{
		fileName = "DaisyExport";
	}

	exportFile.setFileLocation(fileLocation);
	exportFile.setFileName(fileName);
	exportFile.setFileType(IFiles::type::bmp);

	return (exportFile.exportFile(std::move(canvasBuffer), imageInfo));
}

std::pair<float, float> CanvasRenderer::getWindowDPI()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	int widthMM	 = 0;
	int heightMM = 0;
	glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	const float mmToInch = 25.4F;

	float dpiX = (static_cast<float>(mode->width) * mmToInch) / static_cast<float>(widthMM);
	float dpiY = (static_cast<float>(mode->height) * mmToInch) / static_cast<float>(heightMM);

	return {dpiX, dpiY};
}

void CanvasRenderer::renderImage(const IImage& image)
{
	auto [dimWidth, wimHeight] = image.getDimensions();
	auto		imageWidth	   = static_cast<GLsizei>(dimWidth);
	auto		imageHeight	   = static_cast<GLsizei>(wimHeight);
	GLenum		format		   = GL_RGBA;
	GLenum		type		   = GL_UNSIGNED_BYTE;
	const void* pixelData	   = image.getPixelData();

	GLint posX = static_cast<GLint>(image.getCoordinates().first);
	GLint posY = static_cast<GLint>(image.getCoordinates().second + imageHeight);

	int width  = 0;
	int height = 0;
	glfwGetFramebufferSize(window_, &width, &height);

	if (std::cmp_less(height, image.getCoordinates().second) ||
		std::cmp_less(width, image.getCoordinates().first))
	{
		return;
	}

	if (posY > height)
	{
		int	   remRow	= posY - height;
		size_t scanLine = imageWidth * sizeof(int);
		// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
		pixelData = static_cast<const char*>(pixelData) + (remRow * scanLine);
		imageHeight -= remRow;
		posY -= remRow;
	}

	glRasterPos2i(posX, posY);

	glDrawPixels(imageWidth, imageHeight, format, type, pixelData);
}
