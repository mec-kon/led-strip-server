#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H

#include <iostream>

#include "server.h"
#include "file.h"

using namespace std;
class http {
public:
    http();
    void RUN();

private:
    server server_s;
    file file_f;

    string create_header(string message, string content_type, string status_code);
    void handle_request(string request, string mode);
    string get_request_mode(string request);
    string get_content_type(string file_ending);
};


#endif //HTTP_SERVER_HTTP_H
