#ifndef HTTP_SERVER_DATA_H
#define HTTP_SERVER_DATA_H

#include <string>
#include "../../lib/json.hpp"
#include "Color.h"
#include "../defines.h"
using Json = nlohmann::json;
using namespace std;

#define DATA_CPP "data.cpp : "

/**
 * @class data
 *
 * This class extracts all data from the transmitted json file.
 */
class Data {
public:

    Data(string *message);

    Color color_array[ARRAY_SIZE];

    int time;
    string mode;
    int number_of_colors;

    bool is_valid;

};


#endif //HTTP_SERVER_DATA_H
