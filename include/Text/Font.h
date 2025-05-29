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

	// Freetype library cannot be copied or moved
	Font(const Font&)			 = delete;
	Font& operator=(const Font&) = delete;
	Font(Font&&)				 = delete;
	Font& operator=(Font&&)		 = delete;

	[[nodiscard]] FT_Face	getFontFace() const;
	[[nodiscard]] FT_Bitmap getFontBitmap(char c) const;
	void					setFontSize(int size);
	int						getFontSize();

   private:
	FT_Library			  library  = nullptr;
	FT_Face				  face	   = nullptr;
	int					  fontSize = 0;
	std::filesystem::path fontPath;
};

#endif	// FONT_H