#ifndef HTTP_SERVER_MODE_H
#define HTTP_SERVER_MODE_H

#include "Data.h"
#include "../gpio_control/Gpio.h"

#define MODE_CPP "mode.cpp : "

/**
 * @class mode
 *
 * This class takes care of the representation of the different modes.
 */
class Mode {
public:
    Mode();
    Mode(Data *data1, int *mode_is_r);

    void start(sem_t *thread_end);

private:
    int *mode_is_running;
    Data *mode_information;

    void one_color();
    void fade();
    void changing_colors();

};


#endif //HTTP_SERVER_MODE_H
