#include <string>

// Use a .ttf font file for text rendering
class TextClass
{
    public:
     TextClass() = default;
     ~TextClass() = default;

    protected:
        std::string text;
        int		 x;
        int		 y;
        int		 size;
        int		 color[3]; // RGB color


    
};