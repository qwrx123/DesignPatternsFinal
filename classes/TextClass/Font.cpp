#include "Font.h"

Font::Font(std::filesystem::path fontPath) : fontPath(fontPath)
{
	// Initialize FreeType library
	if (FT_Init_FreeType(&library))
	{
		return;
	}

	// Load a font file
	if (!std::filesystem::exists(fontPath))
	{
		return;
	}

	// Load a font face
	if (FT_New_Face(library, fontPath.string().c_str(), 0, &face) != 0)
	{
		return;
	}
}

Font::~Font()
{
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

FT_Face Font::getFontFace() const
{
	return face;
}

FT_Bitmap Font::getFontBitmap(char c) const
{
	// Load the glyph for the character
	FT_UInt glyph_index = FT_Get_Char_Index(face, c);
	if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
	{
		return FT_Bitmap();
	}

	// Render the glyph to a bitmap
	if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
	{
		return FT_Bitmap();
	}

	return face->glyph->bitmap;
}

void Font::setFontSize(int size)
{
	FT_Set_Pixel_Sizes(face, 0, size);
}

int Font::getFontSize()
{
	return fontSize;
}