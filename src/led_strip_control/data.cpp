#include <iostream>
#include "data.h"

data::data(string *message) {

    json json1 = json::parse(*message);

    mode = json1["mode"];

    if (mode == "oneColor") {


        int red = json1["color_array"][0]["color_red"];
        int green = json1["color_array"][0]["color_green"];
        int blue = json1["color_array"][0]["color_blue"];

        color color1(red, green, blue);
        color_array[0] = color1;

    }
    else if (mode == "fade") {
        for (int i = 0; i < ARRAY_SIZE; i++) {

            int red = json1["color_array"][i]["color_red"];
            int green = json1["color_array"][i]["color_green"];
            int blue = json1["color_array"][i]["color_blue"];

            color color1(red, green, blue);
            color_array[i] = color1;
        }
        time = json1["time"];
    }
}