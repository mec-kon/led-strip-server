#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H

#include <iostream>

#include "server.h"
#include "file.h"

using namespace std;
class http {
public:
    http();
    void do_GET();
    void do_POST();

private:
    server server_s;
    file file_f;

    string create_header(string message, string content_type, string status_code);
    void send_response(string request);

};


#endif //HTTP_SERVER_HTTP_H
