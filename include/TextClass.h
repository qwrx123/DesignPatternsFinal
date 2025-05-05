#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include <string>
#include <ft2build.h> 
#include FT_FREETYPE_H

class TextClass
{
    public:
     TextClass();
     ~TextClass();
     void textInput(unsigned int codepoint);
     void renderText();

    protected:
        FT_Library library;
        FT_Face face;
        std::string text;
        FT_UInt glyph_index;
        FT_Bitmap bitmap;
};

#endif // TEXTCLASS_H