#include "Font.h"

Font::Font(std::filesystem::path fontPath) : fontPath(fontPath)
{
    // Initialize FreeType library
    if (FT_Init_FreeType(&library))
    {
        std::cerr << "Could not initialize FreeType library" << std::endl;
        return;
    }

    // Load a font file
    if (!std::filesystem::exists(fontPath))
    {
        std::cerr << "Font file not found: " << fontPath << std::endl;
        return;
    }

    // Load a font face
    if (FT_New_Face(library, fontPath.string().c_str(), 0, &face) != 0)
    {
        std::cerr << "Could not load font" << std::endl;
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
        std::cerr << "Could not load glyph" << std::endl;
        return FT_Bitmap();
    }

    // Render the glyph to a bitmap
    if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
    {
        std::cerr << "Could not render glyph" << std::endl;
        return FT_Bitmap();
    }

    return face->glyph->bitmap;
}