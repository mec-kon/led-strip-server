#include <iostream>
#include "Data.h"

Data::Data(string *message) {
    Json json1;
    int red = 0;
    int green = 0;
    int blue = 0;

    try {
        Json json1 = Json::parse(*message);

        mode = json1["mode"];
        number_of_colors = json1["number_of_colors"];

        if (mode == "oneColor" || number_of_colors == 1) {

            red = json1["color_array"][0]["color_red"];
            green = json1["color_array"][0]["color_green"];
            blue = json1["color_array"][0]["color_blue"];

            Color color1(red, green, blue);
            color_array[0] = color1;

            mode = "oneColor";
        }
        else if (mode == "fade" || mode == "changingColors") {

            if (number_of_colors < 2) {
                Color color1(red, green, blue);
                color_array[0] = color1;
                mode = "oneColor";
            }
            else {
                for (int i = 0; i < number_of_colors; i++) {

                    red = json1["color_array"][i]["color_red"];
                    green = json1["color_array"][i]["color_green"];
                    blue = json1["color_array"][i]["color_blue"];

                    Color color1(red, green, blue);
                    color_array[i] = color1;
                }
                time = json1["time"];
            }
        }
        cout << DATA_CPP << "json data read" << endl;
        is_valid = true;
    }
    catch (Json::parse_error){
        cerr << DATA_CPP << "could not read json data" << endl;
        is_valid = false;
    }



}