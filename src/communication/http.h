#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H

#include <iostream>
#include <semaphore.h>

#include "server.h"
#include "file.h"

#define HTTP "http.cpp : "

using namespace std;

/**
 * @class http
 *
 *This class is responsible for processing HTTP requests and sending HTTP requests.
 */
class http {
public:
    http();
    void RUN(sem_t *network_connection_access, sem_t *network_connection_read, sem_t *network_connection_write , string *message);

private:
    server server_s;
    file file_f;

    string create_header(int message_length, string content_type, string status_code);
    string get_content(string request, int content_length);
    int get_content_length(string request);
    string handle_request(string request, string mode);
    string get_request_mode(string request);
    string get_content_type(string file_ending);
};


#endif //HTTP_SERVER_HTTP_H
