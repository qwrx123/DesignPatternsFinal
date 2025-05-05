#include "TextClass.h"
#include <GLFW/glfw3.h>
#include <ft2build.h>  // FreeType2 header files
#include <filesystem>  // For filesystem operations
#include <iostream>
#include <string>
#include FT_FREETYPE_H	// FreeType2 header files

TextClass::TextClass()
{
	// Initialize FreeType library
	if (FT_Init_FreeType(&library))
	{
		std::cerr << "Could not initialize FreeType library" << std::endl;
		return;
	}

	// Load a font file
	std::filesystem::path fontPath = "../include/Delius-Regular.ttf";

	// Resolve the relative path to an absolute path
	if (!std::filesystem::exists(fontPath))
	{
		std::cerr << "Font file not found: " << fontPath << std::endl;
		return;
	}
	// Load a font face
	else if (FT_New_Face(library, fontPath.string().c_str(), 0, &face) != 0)
	{
		std::cerr << "Could not load font" << std::endl;
		return;
	}
}
TextClass::~TextClass()
{
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextClass::textInput(unsigned int codepoint)
{
	// Convert codepoint to character and add to text string
	char input = '\0';
	input	   = static_cast<char>(codepoint);
	text += input;

	// If backspace remove the last character, ERROR not recognizing the backspace key

	std::cout << "Text: " << text << std::endl;
	std::cout << "Input: " << input << std::endl;
	std::cout << "Codepoint: " << codepoint << std::endl;
}

void TextClass::renderText()
{
	// Set the font size
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Loop through each character in the text string
	for (char c : text)
	{
		// Convert character to codepoint
		unsigned int codepoint = static_cast<unsigned int>(c);

		// Load the glyph for the character
		glyph_index = FT_Get_Char_Index(face, codepoint);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT) != 0)
		{
			std::cerr << "Could not load glyph" << std::endl;
			continue;
		}
		if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL) != 0)
		{
			std::cerr << "Could not render glyph" << std::endl;
			continue;
		}

		FT_Bitmap& bitmap = face->glyph->bitmap;

		glColor3f(1.0f, 1.0f, 1.0f);  // White color for the character
		glRasterPos2f(face->glyph->bitmap_left, face->glyph->bitmap_top);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// Set pixel alignment to 1 byte
		glDrawPixels(bitmap.width, bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);
		// Advance the position for the next character
		glRasterPos2f(face->glyph->advance.x, face->glyph->advance.y);
	}
}
