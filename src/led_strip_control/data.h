#ifndef HTTP_SERVER_DATA_H
#define HTTP_SERVER_DATA_H

#include <string>
#include "../../lib/json.hpp"
#include "color.h"
#include "../defines.h"
using json = nlohmann::json;
using namespace std;

class data {
public:

    data(string *message);

    color color_array[ARRAY_SIZE];

    int time;
    string mode;

};


#endif //HTTP_SERVER_DATA_H
