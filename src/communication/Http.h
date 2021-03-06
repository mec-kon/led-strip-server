#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H

#include <iostream>
#include <semaphore.h>
#include <string>

#include "Server.h"
#include "../file_control/File.h"
#include "../../lib/json.hpp"

#define HTTP_CPP "http.cpp : "

#define WEBSITE_CONFIG 1
#define DEVICE_CONFIG 2

using namespace std;
using Json = nlohmann::json;

/**
 * @class http
 *
 *This class is responsible for processing HTTP requests and sending HTTP requests.
 */
class Http {
public:
    Http();
    void RUN(sem_t *network_connection_access, sem_t *network_connection_read, sem_t *network_connection_write , string *message,  uint8_t *is_configuration_data);

private:
    Server server;
    File file;
    int port;

    uint8_t is_configuration_data_http;

    string create_header(int message_length, string content_type, string status_code);
    string create_cors_header(string cors_ip_address);
    string get_content(string request, int content_length);
    int get_content_length(string request);
    string handle_request(string request, string mode);
    string get_request_mode(string request);
    string get_content_type(string file_ending);
};


#endif //HTTP_SERVER_HTTP_H
