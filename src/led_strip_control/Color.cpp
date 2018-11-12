#include "Color.h"

Color::Color(){
}
Color::Color(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
}

bool Color::operator==(const Color &color2) const{
    return (red==color2.red) && (blue==color2.blue) && (green==color2.green);
}
bool Color::operator!=(const Color &color2) const{
    return (red!=color2.red) || (blue!=color2.blue) || (green==color2.green);
}