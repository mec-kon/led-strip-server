#include <chrono>
#include <thread>
#include <semaphore.h>
#include "mode.h"

mode::mode(data *data1,int *mode_is_r) {
    mode_information = data1;
    mode_is_running = mode_is_r;

    cout << MODE << "constructor method called" << endl;
}


void mode::start(sem_t *thread_end) {
    sem_wait(thread_end);
    cout << MODE << "current mode started" << endl;
    switch (mode_information->mode){
        case 'o':
            cout << MODE << "mode = one color" << endl;
            one_color();
            break;
        case 'f':
            cout << MODE << "mode = fade" << endl;
            fade();
            break;
        default: one_color();
            break;
    }
    sem_post(thread_end);
    cout << MODE << "current mode stopped" << endl;
}

void mode::one_color() {
    pwm_write(GPIO_RED, mode_information->color_array[0].red);
    pwm_write (GPIO_GREEN, mode_information->color_array[0].green);
    pwm_write (GPIO_BLUE, mode_information->color_array[0].blue);

    }

void mode::fade() {
    int i = 0;
    color color1;
    color color2;

    while(*mode_is_running){



        if(i==mode_information->number_of_colors-1){
            color1 = mode_information->color_array[4];
            color2 = mode_information->color_array[0];
            i++;
        }
        else{
            if(i==mode_information->number_of_colors){
                i=0;
            }
            color1 = mode_information->color_array[i];
            color2 = mode_information->color_array[i+1];
            i++;
        }
        while(color1.red != color2.red || color1.blue != color2.blue || color1.green != color2.green){
            if(color1.red > color2.red){
                color1.red--;
            }
            else if (color1.red < color2.red){
                color1.red++;
            }

            if(color1.green > color2.green){
                color1.green--;
            }
            else if (color1.green < color2.green){
                color1.green++;
            }

            if(color1.blue > color2.blue){
                color1.blue--;
            }
            else if (color1.blue < color2.blue){
                color1.blue++;
            }

            pwm_write (GPIO_RED, color1.red);
            pwm_write (GPIO_GREEN, color1.green);
            pwm_write (GPIO_BLUE, color1.blue);

            this_thread::sleep_for(chrono::milliseconds(mode_information->time));
        }

    }

}