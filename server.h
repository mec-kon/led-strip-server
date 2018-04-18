#ifndef HTTP_SERVER_SERVER_H
#define HTTP_SERVER_SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "defines.h"


using namespace std;

class server {

public:

    void create_server();
    string receive_data();
    void send_data(string message);
    void detach();
    void close_connection();

private:

    int socket_s;
    int connection_c;

};

#endif //HTTP_SERVER_SERVER_H