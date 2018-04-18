#ifndef HTTP_SERVER_SERVER_H
#define HTTP_SERVER_SERVER_H

#include <stdio.h>

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define PORT 10000
#define FILE_PATH "../"
#define MAX_PACKET_SIZE 4096
#define MAX_POSSIBLE_CONNECTIONS 5

#define CREATION_ERROR_MESSAGE "error! could not create socket"


using namespace std;

class server {

public:

    void create_server();
    void receive_data();
    void send_data(string message);
    void detach();

private:

    int socket_s;
    int connection_c;
    string create_header(string message, string content_type);
    string open_file(string filename);
    void send_response(string request);
    string get_filename(string request);
    string get_fileending(string filename);

};

#endif //HTTP_SERVER_SERVER_H