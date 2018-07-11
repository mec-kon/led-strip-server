#include <iostream>
#include "data.h"

data::data(string *message) {

    json json1 = json::parse(*message);

    color.red = json1["color_red"];
    color.green = json1["color_green"];
    color.blue = json1["color_blue"];

    time = 0;
    mode = 'o';

    /*
    mode = json1["mode"];

    if(json1["time"] != NULL){
        time = json1["time"];
    }
    else{
        time = 0;
    }
     */
}