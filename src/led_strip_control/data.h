#ifndef HTTP_SERVER_DATA_H
#define HTTP_SERVER_DATA_H

#include <string>
#include "../../lib/json.hpp"
#include "color.h"
#include "../defines.h"
using json = nlohmann::json;
using namespace std;

#define DATA "data.cpp : "

/**
 * @class data
 *
 * This class extracts all data from the transmitted json file.
 */
class data {
public:

    data(string *message);

    color color_array[ARRAY_SIZE];

    int time;
    string mode;
    int number_of_colors;

    bool is_valid;

};


#endif //HTTP_SERVER_DATA_H
