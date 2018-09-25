#include <chrono>
#include <thread>
#include <semaphore.h>
#include "mode.h"

mode::mode(data *data1,int *mode_is_r) {
    mode_information = data1;
    mode_is_running = mode_is_r;
}


void mode::start(sem_t *thread_end) {
    sem_wait(thread_end);
    switch (mode_information->mode){
        case 'o': one_color();
            break;
        case 'f': fade();
            break;
        default: one_color();
            break;
    }

    sem_post(thread_end);
}

void mode::one_color() {
    cout<<"mode = one color"<<endl;

    pwm_write(GPIO_RED, mode_information->color_array[0].red);
    pwm_write (GPIO_GREEN, mode_information->color_array[0].green);
    pwm_write (GPIO_BLUE, mode_information->color_array[0].blue);
}

void mode::fade() {
    int i = 0;
    color color1;
    color color2;

    cout<<"mode = fade"<<endl;

    while(*mode_is_running){

        cout<<"mode_is_running" << *mode_is_running <<endl;


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
        cout<< color1.red << color2.red << endl;
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
            else if (color1.green< color2.green){
                color1.green++;
            }

            if(color1.blue > color2.blue){
                color1.blue--;
            }
            else if (color1.blue< color2.blue){
                color1.blue++;
            }

            pwm_write (GPIO_RED, color1.red);
            pwm_write (GPIO_GREEN, color1.green);
            pwm_write (GPIO_BLUE, color1.blue);
        }

        this_thread::sleep_for(chrono::milliseconds(mode_information->time));
    }

}