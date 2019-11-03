#include "Settings.h"

Settings::Settings(string json_string)
{
    try {
        posted_json = Json::parse(json_string);
    } catch (Json::parse_error) {
        cerr << "Settings: error" << endl;
        cerr << json_string << endl;
    }
}

DeviceSettings::DeviceSettings(string message) : Settings (message){
    try {
        string config_file = file.open_file("deviceConfig.json");
        config_file_json = Json::parse(config_file);
    } catch (Json::parse_error) {
        cerr << "DeviceSettings: error" << endl;
    }



    // special iterator member functions for objects
    for (Json::iterator i = posted_json["devices"].begin(); i != posted_json["devices"].end(); i++) {

        if(!i.value()["name"].is_null()){
            string name = i.value()["name"];
            bool found = false;
            for (Json::iterator j = config_file_json["devices"].begin(); j != config_file_json["devices"].end(); j++) {
                if(j.value()["name"]== name){
                    j.value()["ipAddress"] = i.value()["ipAddress"];
                    j.value()["port"] = i.value()["port"];
                    found = true;
                    break;
                }
            }
            if(!found){
                config_file_json["devices"].push_back(i.value());
            }
        }
    }

    file.write_file("deviceConfig.json", config_file_json.dump(4));

#ifdef DEBUG_MODE
    cout << SETTINGS_CPP << "new device settings saved" << endl;
#endif

}

WebsiteSettings::WebsiteSettings(string message) : Settings (message){
    try {
        string config_file = file.open_file("websiteConfig.json");
        config_file_json = Json::parse(config_file);
    } catch (Json::parse_error) {
        cerr << "WebsiteSettings: error" << endl;
    }

    for (Json::iterator i = posted_json.begin(); i != posted_json.end(); i++) {
        if(config_file_json[i.key()] != i.value() && i.value() != NULL){
            config_file_json[i.key()] = i.value();
        }
    }
    file.write_file("websiteConfig.json", config_file_json.dump(4));

#ifdef DEBUG_MODE
    cout << SETTINGS_CPP << "new website settings saved" << endl;
#endif
}
