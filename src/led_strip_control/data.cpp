#include <iostream>
#include "data.h"

data::data(string *message) {
    json json1;
    int red = 0;
    int green = 0;
    int blue = 0;

    try {
        json json1 = json::parse(*message);

        mode = json1["mode"];
        number_of_colors = json1["number_of_colors"];

        if (mode == "oneColor" || number_of_colors == 1) {

            red = json1["color_array"][0]["color_red"];
            green = json1["color_array"][0]["color_green"];
            blue = json1["color_array"][0]["color_blue"];

            color color1(red, green, blue);
            color_array[0] = color1;

            mode = "oneColor";
        }
        else if (mode == "fade" || mode == "changingColors") {

            if (number_of_colors < 2) {
                color color1(red, green, blue);
                color_array[0] = color1;
                mode = "oneColor";
            }
            else {
                for (int i = 0; i < number_of_colors; i++) {

                    red = json1["color_array"][i]["color_red"];
                    green = json1["color_array"][i]["color_green"];
                    blue = json1["color_array"][i]["color_blue"];

                    color color1(red, green, blue);
                    color_array[i] = color1;
                }
                time = json1["time"];
            }
        }
        cout << DATA << "json data read" << endl;
        is_valid = true;
    }
    catch (json::parse_error){
        cerr << DATA << "could not read json data" << endl;
        is_valid = false;
    }



}