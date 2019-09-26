#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <string>

#include "../../lib/json.hpp"
#include "../file_control/File.h"

#define WEBSITE_CONFIG 1
#define DEVICE_CONFIG 2

using Json = nlohmann::json;
using namespace std;


class Settings
{
public:
    Settings(string json_string);

protected:
    Json posted_json;
    Json config_file_json;
    File file;
};

class DeviceSettings : Settings
{
public:
    DeviceSettings(string message);
};

class WebsiteSettings : Settings
{
public:
    WebsiteSettings(string message);
};

#endif // SETTINGS_H
