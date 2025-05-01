#include <string>
#include <ft2build.h> // FreeType2 header files
#include FT_FREETYPE_H // FreeType2 header files
// Use a .ttf font file for text rendering
class TextClass
{
    public:
     TextClass() = default;
     ~TextClass() = default;
     FT_Library library;
     FT_Face face;
     error = FT_Init_FreeType(&library);
     error = FT_New_Face(library, "path/to/font.ttf", 0, &face);

    protected:
        std::string text;
        int		 x;
        int		 y;
        int		 size;
        int		 color[3]; // RGB color


    
};