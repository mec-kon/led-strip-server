#include "mode.h"

mode::mode(data *data1) {
    mode_information = data1;
}

void mode::start() {
    switch (mode_information->mode){
        case 'o': one_color();
            break;
        default: one_color();
            break;
    }
}

void mode::one_color() {
    pwm_write(GPIO_RED, mode_information->color.red);
    pwm_write (GPIO_GREEN, mode_information->color.green);
    pwm_write (GPIO_BLUE, mode_information->color.blue);
}