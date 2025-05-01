#include "TextClass.h"
#include <GLFW/glfw3.h>
#include <ft2build.h>  // FreeType2 header files
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

	// Load a font face
	if (FT_New_Face(library, "path/to/font.ttf", 0, &face))
	{
		std::cerr << "Could not load font" << std::endl;
		return;
	}

	// Set the font size
	FT_Set_Pixel_Sizes(face, 0, 48);  // Set font size to 48 pixels
}
TextClass::~TextClass()
{
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextClass::textInput(unsigned int codepoint)
{
	// Convert codepoint to character and add to text string
	char input = static_cast<char>(codepoint);
	text += input;
	std::cout << "Input: " << input << std::endl;
	glyph_index = FT_Get_Char_Index(face, codepoint);
	FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
}
