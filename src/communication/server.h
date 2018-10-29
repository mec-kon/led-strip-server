#ifndef HTTP_SERVER_SERVER_H
#define HTTP_SERVER_SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../defines.h"


using namespace std;

/**
 * @class server
 *
 * This class is responsible for the TCP connection over a socket.
 * An object of this class is used in the class http.
 */
class server {

public:

    void create_server(int port);
    string receive_data();
    void send_data(string message);
    void detach();
    void close_connection();

private:

    int socket_s;
    int connection_c;

};

#endif //HTTP_SERVER_SERVER_H