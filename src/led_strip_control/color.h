#ifndef HTTP_SERVER_COLOR_H
#define HTTP_SERVER_COLOR_H


class color {
public:
    color();
    bool operator==(const color &color2) const;
    bool operator!=(const color &color2) const;

    int red;
    int green;
    int blue;

};


#endif //HTTP_SERVER_COLOR_H
