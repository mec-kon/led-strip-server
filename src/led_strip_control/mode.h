#ifndef HTTP_SERVER_MODE_H
#define HTTP_SERVER_MODE_H

#include "data.h"
#include "../gpio_control/gpio.h"

class mode {
    data *mode_information;

public:
    mode(data *data1);
    void start();

private:
    void one_color();

};


#endif //HTTP_SERVER_MODE_H
