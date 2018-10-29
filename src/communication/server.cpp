#include <iostream>
#include <fstream>
#include "server.h"

/**
 * @brief this method initializes a socket
 *
 * This method configures a socket for ipv4, tcp and the port specified in the defines.h file.
 *
 * @return void
 */
void server::create_server(int port) {
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET; //internet ip protocol v4
    my_addr.sin_port = htons(port); //PORT
    my_addr.sin_addr.s_addr = INADDR_ANY; //network byte order

    //create socket
    if ((socket_s = socket(my_addr.sin_family, SOCK_STREAM, 0)) == -1) {
        cout << CREATION_ERROR_MESSAGE << endl;
    }

    //bind socket to a PORT
    bind(socket_s, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));

    // listen up to MAX_POSSIBLE_CONNECTIONS connections
    listen(socket_s, MAX_POSSIBLE_CONNECTIONS);
}

/**
 * @brief this method is for receiving data
 *
 * This method can be used to receive data of the size MAX_PACKET_SIZE, which is defined in defines.h.
 *
 * @return request
 */
string server::receive_data() {
    socklen_t sock_size = sizeof(struct sockaddr_in);

    struct sockaddr_in host_addr;

    //waiting for connection
    connection_c = accept(socket_s, (struct sockaddr *) &host_addr, &sock_size);

    //receive data contend
    char data[MAX_PACKET_SIZE];
    recv(connection_c, data, MAX_PACKET_SIZE, 0);  //GET / HTTP/1.1

    return data;
}

/**
 * @brief this method is for sending data
 *
 * @param message
 */
void server::send_data(string message) {
    send(connection_c, message.c_str(), message.length(), 0);
}

/**
 * @brief this method closes a socket
 */
void server::detach() {
    close(socket_s);
    close(connection_c);
}

/**
 * @brief this method closes a connection
 */
void server::close_connection() {
    close(connection_c);
}