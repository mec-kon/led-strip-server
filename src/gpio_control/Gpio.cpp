#include "Gpio.h"


void gpio_init(){

#ifdef IS_RASPBERRY_PI
    wiringPiSetup();

    pinMode(GPIO_RED, PWM_OUTPUT); // Set PWM LED as PWM output
    pinMode(GPIO_GREEN, PWM_OUTPUT); // Set PWM LED as PWM output
    pinMode(GPIO_BLUE, PWM_OUTPUT); // Set PWM LED as PWM output


    softPwmCreate (GPIO_RED, 0, 64) ;
    softPwmCreate (GPIO_GREEN, 0, 64) ;
    softPwmCreate (GPIO_BLUE, 0, 64) ;

#endif
#ifdef DEBUG_MODE
    cout << GPIO_CPP << "GPIO init" << endl;
#endif
}

void pwm_write(int gpio, int value){
#ifdef IS_RASPBERRY_PI
    softPwmWrite (gpio, value/4);
#endif
#ifdef DEBUG_MODE
    cout << GPIO_CPP << "GPIO : " << gpio << " VALUE : " << value << endl;
#endif
}
