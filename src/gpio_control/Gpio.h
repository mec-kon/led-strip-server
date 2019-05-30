#ifndef HTTP_SERVER_GPIO_H
#define HTTP_SERVER_GPIO_H

#include <iostream>

#include "../defines.h"

#define GPIO "gpio.cpp : "

using namespace std;

#ifdef IS_RASPBERRY_PI
#include <wiringPi.h>
#include <softPwm.h>
#endif

extern void gpio_init();
extern void pwm_write(int gpio, int value);

#endif //HTTP_SERVER_GPIO_H
