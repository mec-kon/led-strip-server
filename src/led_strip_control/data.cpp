#include <iostream>
#include "data.h"

data::data(string *message) {

    json json1 = json::parse(*message);

    for(int i=0; i<5; i++){
        color_array[i].red = json1["color_red"];
        color_array[i].green = json1["color_green"];
        color_array[i].blue = json1["color_blue"];
    }

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