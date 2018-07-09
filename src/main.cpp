#include <iostream>
#include <thread>
#include <mutex>


#include "communication/http.h"

#include "../lib/json.hpp"
using json = nlohmann::json;

using namespace std;

static http http1;

mutex *network_connection;

string *message;
bool *new_message;

void thread_handler(){
    while(true){
        network_connection->lock();

        if(*new_message == true){
            cout << "true "<< endl << endl;
        }
        else{
            cout << "false" << endl;
        }

        network_connection->unlock();
    }

}

void thread_init(){
    thread network_thread(&http::RUN, &http1, network_connection, message, new_message);
    thread administrative_thread(thread_handler);

    network_thread.join();
    administrative_thread.join();
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
int main()
{
    network_connection = new mutex();

    message = new string();
    new_message = new bool();


    thread_init();

    cout << "end" << endl;

    return 0;
}