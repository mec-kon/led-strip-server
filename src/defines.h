#ifndef HTTP_SERVER_DEFINES_H
#define HTTP_SERVER_DEFINES_H

/**
 * @file defines.h
 *
 * This file contains all parameters that can be configured
 */
#define MQTT_CLIENT_ID "led-strip-server"
#define MQTT_CLIENT "client-name"
#define MQTT_CLIENT_PASSWORD "passw0rd"
#define MQTT_PUBLISH_TOPIC "home/ledstripserver"
#define MQTT_SUBSCRIPTION_TOPIC "home/ledstripserver"

#define MQTT_ADDRESS "127.0.0.1"
#define MQTT_PORT 1883


#define STATIC_PATH "../static/src/"
#define INSTALLED_STATIC_PATH "/.led-strip-server/src/"
#define CONFIG_PATH "../config/"
#define INSTALLED_CONFIG_PATH "/.led-strip-server/config/"
#define MAX_PACKET_SIZE 4096
#define MAX_POSSIBLE_CONNECTIONS 5

#define CREATION_ERROR_MESSAGE "error! could not create socket"


#define GPIO_RED 2
#define GPIO_GREEN 0
#define GPIO_BLUE 3

#define ARRAY_SIZE 6

#endif //HTTP_SERVER_DEFINES_H
