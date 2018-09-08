#ifndef HTTP_SERVER_MODE_H
#define HTTP_SERVER_MODE_H

#include "data.h"
#include "../gpio_control/gpio.h"

class mode {
public:
    mode(data *data1);
    void start();

private:
    data *mode_information;
    void one_color();
    void fade();

};


#endif //HTTP_SERVER_MODE_H
