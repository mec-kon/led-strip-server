#ifndef HTTP_SERVER_COLOR_H
#define HTTP_SERVER_COLOR_H

/**
 * @class color
 *
 * This class is used to save a color.
 */
class Color {
public:
    Color();
    Color(int r, int g, int b);
    bool operator==(const Color &color2) const;
    bool operator!=(const Color &color2) const;

    int red;
    int green;
    int blue;

};


#endif //HTTP_SERVER_COLOR_H
