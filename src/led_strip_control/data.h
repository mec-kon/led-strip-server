#ifndef HTTP_SERVER_COLOR_H
#define HTTP_SERVER_COLOR_H

#include <string>
#include "../../lib/json.hpp"
using json = nlohmann::json;
using namespace std;

class data {
public:

    data(string *message);

    struct colors {
        int red;
        int green;
        int blue;
    } color;

    int time;
    int mode;

};


#endif //HTTP_SERVER_COLOR_H
