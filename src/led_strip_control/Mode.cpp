#include <chrono>
#include <thread>
#include <semaphore.h>
#include "Mode.h"

Mode::Mode() {
    mode_information = nullptr;
    mode_is_running = nullptr;
}

Mode::Mode(Data *data1, int *mode_is_r) {
    mode_information = data1;
    mode_is_running = mode_is_r;

    cout << MODE << "constructor method called" << endl;
}

/**
 * @brief method to start the choosen mode
 *
 * This method starts the mode selected on the web page.
 * It is started in the main function in its own thread.
 *
 * @param thread_end
 */
void Mode::start(sem_t *thread_end) {
    sem_wait(thread_end);
    cout << MODE << "current mode started" << endl;

    if (mode_information->mode == "fade") {
        cout << MODE << "mode = fade" << endl;
        fade();
    }
    else if(mode_information->mode == "changingColors"){
        cout << MODE << "mode = changingColors" << endl;
        changing_colors();
    }
    else {
        cout << MODE << "mode = one color" << endl;
        one_color();
    }

    sem_post(thread_end);
    cout << MODE << "current mode stopped" << endl;
}

void Mode::one_color() {
    pwm_write(GPIO_RED, mode_information->color_array[0].red);
    pwm_write(GPIO_GREEN, mode_information->color_array[0].green);
    pwm_write(GPIO_BLUE, mode_information->color_array[0].blue);

}

void Mode::fade() {
    int i = 0;
    Color color1;
    Color color2;


    while (*mode_is_running) {


        if (i == mode_information->number_of_colors - 1) {
            color1 = mode_information->color_array[mode_information->number_of_colors - 1];
            color2 = mode_information->color_array[0];
        }
        else {
            if (i == mode_information->number_of_colors) {
                i = 0;
            }
            color1 = mode_information->color_array[i];
            color2 = mode_information->color_array[i + 1];
        }
        i++;
        while (color1.red != color2.red || color1.blue != color2.blue || color1.green != color2.green) {
            if (!(*mode_is_running)) {
                break;
            }


            if (color1.red > color2.red) {
                color1.red--;
            }
            else if (color1.red < color2.red) {
                color1.red++;
            }

            if (color1.green > color2.green) {
                color1.green--;
            }
            else if (color1.green < color2.green) {
                color1.green++;
            }

            if (color1.blue > color2.blue) {
                color1.blue--;
            }
            else if (color1.blue < color2.blue) {
                color1.blue++;
            }

            pwm_write(GPIO_RED, color1.red);
            pwm_write(GPIO_GREEN, color1.green);
            pwm_write(GPIO_BLUE, color1.blue);

            this_thread::sleep_for(chrono::milliseconds(mode_information->time));
        }
    }
}

void Mode::changing_colors() {
    int i = 0;
    Color color1;
    while (*mode_is_running) {
        if (i == mode_information->number_of_colors) {
            i = 0;
        }
        color1 = mode_information->color_array[i];
        i++;

        pwm_write(GPIO_RED, color1.red);
        pwm_write(GPIO_GREEN, color1.green);
        pwm_write(GPIO_BLUE, color1.blue);

        this_thread::sleep_for(chrono::milliseconds(mode_information->time*10));
    }
}