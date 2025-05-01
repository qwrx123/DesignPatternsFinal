#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include <string>
#include <ft2build.h> 
#include FT_FREETYPE_H

// Use a .ttf font file for text rendering
class TextClass
{
    public:
     TextClass();
     ~TextClass();
     void textInput(unsigned int codepoint);

    protected:
        FT_Library library;
        FT_Face face;
        std::string text;
        FT_UInt glyph_index;
    
};

#endif // TEXTCLASS_H