#ifndef HTTP_SERVER_MODE_H
#define HTTP_SERVER_MODE_H

#include "data.h"
#include "../gpio_control/gpio.h"

#define MODE "mode.cpp : "

class mode {
public:
    mode();
    mode(data *data1, int *mode_is_r);

    void start(sem_t *thread_end);

private:
    int *mode_is_running;
    data *mode_information;

    void one_color();

    void fade();

};


#endif //HTTP_SERVER_MODE_H
