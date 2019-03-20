#ifndef SIMPLE_MQTT_CLIENT_MQTT_H
#define SIMPLE_MQTT_CLIENT_MQTT_H

#include <mosquittopp.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <semaphore.h>

#include "../File.h"
#include "../../lib/json.hpp"

#define MQTT "mqtt.cpp: "

using namespace std;
using Json = nlohmann::json;

/**
 * @class Mqtt
 * This class is responsible for the mqtt connection using mosquittopp.
 */
class Mqtt : public mosqpp::mosquittopp {
private:
    string id;
    string host;
    string publish_topic;
    vector<string> subscription_topic_list;
    int port;

    sem_t *network_connection_access;
    sem_t *network_connection_read;
    sem_t *network_connection_write;
    string *message;


    /**
     * the number of seconds after which the broker should send a PING message to the client if no other messages have
     * been exchanged in that time
     */
    int keepalive;

    void on_connect(int rc);

    void on_disconnect(int rc);

    void on_publish(int mid);

    void on_subscribe(int /*mid*/, int /*qos_count*/, const int */*granted_qos*/);

    /**
     * @brief callback function
     *
     * callback function that is called when a new message is received
     *
     * @param message structure that contains the message as payload, among other things
     */
    void on_message(const struct mosquitto_message *message);

public:
    /**
     * @brief constructor
     *
     * This is the constructor of the mqtt class.
     *
     * @param publish_topic null terminated string of the topic to publish to
     * @param subscribe_topic the subscription pattern
     * @param host the hostname or ip address of the broker to connect to
     * @param port the network port to connect to (usually 1883)
     */
    Mqtt(string id, string publish_topic,vector<string> subscription_topic_list, string host,
            sem_t *network_connection_access, sem_t *network_connection_read, sem_t *network_connection_write,
            string *message);

    ~Mqtt();

    /**
     * @brief publish a message on a given topic
     * @param message null terminated string of the topic to publish to
     * @return True, if publication was successfully
     */
    bool publish(string message);

    /**
     * @brief subscribe to a topic
     * @return True, if subscription was successfully
     */
    bool subscribe();
};


#endif //SIMPLE_MQTT_CLIENT_MQTT_H
