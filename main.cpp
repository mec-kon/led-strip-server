#include <iostream>
#include "server.h"

int main()
{

    server s;

    s.create_server();
    s.receive_data();
    s.detach();

    return 0;
}