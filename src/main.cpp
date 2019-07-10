#include <iostream>
#include <thread>
#include <semaphore.h>


#ifdef USE_MQTT
#include "communication/Mqtt.h"
#endif

#include "communication/Http.h"
#include "led_strip_control/Data.h"
#include "led_strip_control/Mode.h"
#include "gpio_control/Gpio.h"

#define MAIN "main.cpp : "

using namespace std;

Http http;

#ifdef USE_MQTT
Mqtt *mqtt = nullptr;
#endif

sem_t *network_connection_access;
sem_t *network_connection_read;
sem_t *network_connection_write;

sem_t *thread_end;

string *message;

/**
 * @brief method to process data
 * Received data is processed in this method.
 * When a new string is received, this method starts a new thread that executes the sent mode.
 */
void thread_handler() {
    Mode *mode1 = new Mode();
    thread color_thread;
    int *mode_is_running = new int(0);

    while (true) {
        sem_wait(network_connection_read);
        sem_wait(network_connection_access);

#ifdef DEBUG_MODE
        cout << MAIN << "data received in thread_handler()" << endl;
#endif

        Data data1(message);

        if(data1.is_valid){
            *mode_is_running = 0;

            sem_wait(thread_end);
            delete mode1;
            *mode_is_running = 1;
            mode1 = new Mode(&data1, mode_is_running);
            sem_post(thread_end);
            color_thread = thread(&Mode::start, mode1, thread_end);
            color_thread.detach();
#ifdef DEBUG_MODE
            cout << MAIN << "color_thread created in thread_handler()" << endl;
#endif
        }
        else {
            cerr << MAIN << "received data invalid" << endl;
        }



        sem_post(network_connection_access);
        sem_post(network_connection_write);
    }

}

/**
 * @brief method to initialize two used threads
 * One of the two threads takes care of the network connection,
 * the other thread takes care of processing the received data.
 *
 * @return void
 */
void thread_init() {
#ifdef DEBUG_MODE
    cout << MAIN << "initializing threads in thread_init()" << endl;
#endif
#ifdef USE_MQTT
    vector<string> subscription_topic_list;
    subscription_topic_list.push_back(MQTT_SUBSCRIPTION_TOPIC);

   /*
    * if no authentication is required
    *
    * mqtt = new Mqtt(MQTT_CLIENT_ID, MQTT_PUBLISH_TOPIC, subscription_topic_list, MQTT_ADDRESS, MQTT_PORT,
                network_connection_access, network_connection_read, network_connection_write, message);
    */

    mqtt = new Mqtt(MQTT_CLIENT_ID, MQTT_PUBLISH_TOPIC, subscription_topic_list, MQTT_ADDRESS, MQTT_PORT,
            network_connection_access, network_connection_read, network_connection_write, message, MQTT_CLIENT, MQTT_CLIENT_PASSWORD);
    mqtt->subscribe();
#endif
    thread network_thread(&Http::RUN, &http, network_connection_access, network_connection_read,
                          network_connection_write, message);
    thread administrative_thread(thread_handler);
    network_thread.join();
    administrative_thread.join();

}

/**
 * @brief method to initialize all used semaphores
 *
 * In this method, four semaphores are initialized.
 * The first three are to solve the producer-consumer problem.
 * The fourth semaphore ensures that the thread_handler
 * method waits with the processing of new data until the old led mode is terminated.
 *
 * @return void
 */
void semaphore_init() {
    network_connection_access = (sem_t *) malloc(sizeof(sem_t));
    sem_init(network_connection_access, 0, 1);

    network_connection_read = (sem_t *) malloc(sizeof(sem_t));
    sem_init(network_connection_read, 0, 0);

    network_connection_write = (sem_t *) malloc(sizeof(sem_t));
    sem_init(network_connection_write, 0, 1);

    thread_end = (sem_t *) malloc(sizeof(thread_end));
    sem_init(thread_end, 0, 1);

#ifdef DEBUG_MODE
    cout << MAIN << "semaphores initialized in semaphore_init()" << endl;
#endif
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
