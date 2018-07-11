#ifndef HTTP_SERVER_GPIO_H
#define HTTP_SERVER_GPIO_H

#include <iostream>

#include "../defines.h"

using namespace std;

#ifdef __arm__
#include <wiringPi.h>
#include <softPwm.h>
#include "config.h"
#endif

extern void gpio_init();
extern void pwm_write(int gpio, int value);

#endif //HTTP_SERVER_GPIO_H
