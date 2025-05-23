#ifndef FONT_H
#define FONT_H
#include <filesystem>
#include <ft2build.h>
#include FT_FREETYPE_H

class Font
{
   public:
	Font(const std::filesystem::path& fontPath);
	~Font();
	[[nodiscard]] FT_Face	getFontFace() const;
	[[nodiscard]] FT_Bitmap getFontBitmap(char c) const;

   private:
	FT_Library			  library = nullptr;
	FT_Face				  face	  = nullptr;
	std::filesystem::path fontPath;
};

#endif	// FONT_H