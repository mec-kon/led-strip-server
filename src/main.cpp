#include <iostream>
#include <thread>
#include <semaphore.h>


#include "communication/http.h"
#include "led_strip_control/data.h"
#include "led_strip_control/mode.h"
#include "gpio_control/gpio.h"


using namespace std;

http http1;

sem_t *network_connection_access;
sem_t *network_connection_read;
sem_t *network_connection_write;

sem_t *thread_end;

string *message;

void thread_handler() {
    mode *mode1;
    thread color_thread;
    int *mode_is_running =new int(0);

    while (true) {
        sem_wait(network_connection_read);
        sem_wait(network_connection_access);
        cout << "received data in thread 2 : " << *message << endl;


        *mode_is_running = 0;

        sem_wait(thread_end);
        data data1(message);
        delete mode1;
        *mode_is_running = 1;
        mode1 = new mode(&data1, mode_is_running);
        sem_post(thread_end);
        color_thread = thread(&mode::start, mode1, thread_end);
        color_thread.detach();

        sem_post(network_connection_access);
        sem_post(network_connection_write);
    }

}

void thread_init() {
    thread network_thread(&http::RUN, &http1, network_connection_access, network_connection_read,
                          network_connection_write, message);
    thread administrative_thread(thread_handler);

    network_thread.join();
    administrative_thread.join();
}

void semaphore_init() {
    network_connection_access = (sem_t *) malloc(sizeof(network_connection_access));
    sem_init(network_connection_access, 0, 1);

    network_connection_read = (sem_t *) malloc(sizeof(network_connection_read));
    sem_init(network_connection_read, 0, 0);

    network_connection_write = (sem_t *) malloc(sizeof(network_connection_write));
    sem_init(network_connection_write, 0, 1);

    thread_end = (sem_t *) malloc(sizeof(thread_end));
    sem_init(thread_end, 0, 1);
}


/**
 * @brief main function
 *
 * This is the main function of the program.
 * In this function, an object of the class http is created,
 * which starts the RUN function, which waits for connections in an endless loop and processes them.
 *
 * @return 0
 */
int main() {
    message = new string();

    gpio_init();
    semaphore_init();
    thread_init();

    return 0;
}
