#include <iostream>
#include "data.h"

data::data(string *message) {

    json json1 = json::parse(*message);

    for(int i=0; i<5; i++){
        color_array[i].red = json1["color_red"][i];
        color_array[i].green = json1["color_green"][i];
        color_array[i].blue = json1["color_blue"][i];
    }

    time = 100;
    mode = json1["mode"];

    number_of_colors = 5;

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