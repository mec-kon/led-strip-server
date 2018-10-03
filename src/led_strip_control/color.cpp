#include "color.h"

color::color(){
}
color::color(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
}

bool color::operator==(const color &color2) const{
    return (red==color2.red) && (blue==color2.blue) && (green==color2.green);
}
bool color::operator!=(const color &color2) const{
    return (red!=color2.red) || (blue!=color2.blue) || (green==color2.green);
}