#ifndef HTTP_SERVER_DATA_H
#define HTTP_SERVER_DATA_H

#include <string>
#include "../../lib/json.hpp"
#include "color.h"
using json = nlohmann::json;
using namespace std;

class data {
public:

    data(string *message);

    color color_array[5];

    int time;
    int mode;
    int number_of_colors;

};


#endif //HTTP_SERVER_DATA_H
