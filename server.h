#ifndef HTTP_SERVER_SERVER_H
#define HTTP_SERVER_SERVER_H

#include <stdio.h>

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define PORT 10000
#define MAX_PACKET_SIZE 4096
#define MAX_POSSIBLE_CONNECTIONS 5
#define WELCOME_MESSAGE "welcome on this server"
#define CREATION_ERROR_MESSAGE "error! could not create socket"


using namespace std;

class server {

public:

    int socket_s;
    int connection_c;

    void create_server();
    void receive_data();
    void send_data();
    void detach();

};

#endif //HTTP_SERVER_SERVER_H