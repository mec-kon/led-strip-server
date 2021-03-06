#include "Mqtt.h"

Mqtt::Mqtt(string id, string publish_topic,vector<string> subscription_topic_list, string host, int port,
           sem_t *network_connection_access, sem_t *network_connection_read, sem_t *network_connection_write,
           string *message, string username, string password) : mosquittopp(id.c_str())
{
    connected = false;


    /*
    File file;
    string config = file.open_file("websiteConfig.json");
    Json json;
    try {
        json = Json::parse(config);
        this->port = json["mqttPort"];
        this->host = json["mqttHost"];
    }
    catch (exception &e) {
        cerr << MQTT << "could not read websiteConfig.json" << endl;
        cerr << MQTT << "error: " << e.what() << endl;
#ifdef DEBUG_MODE
        cout << MQTT << "Server created with default mqtt-port 1883 on 127.0.0.1" << endl;
#endif
        this->port = 1883;
        this->host = "127.0.0.1";
    }
    */


    mosqpp::lib_init();
    this->id = id;
    this->keepalive = 60;
    this->host = host;
    this->port = port;
    this->publish_topic = publish_topic;
    this->subscription_topic_list = subscription_topic_list;

    this->network_connection_access = network_connection_access;
    this->network_connection_read = network_connection_read;
    this->network_connection_write = network_connection_write;
    this->message = message;

    mosquittopp::username_pw_set(username.c_str(), password.c_str());


};



Mqtt::Mqtt(string id, string publish_topic,vector<string> subscription_topic_list, string host, int port,
           sem_t *network_connection_access, sem_t *network_connection_read, sem_t *network_connection_write,
           string *message) : mosquittopp(id.c_str())
{
    connected = false;

    /*
    File file;
    string config = file.open_file("websiteConfig.json");
    Json json;
    try {
        json = Json::parse(config);
        this->port = json["mqttPort"];
        this->host = json["mqttHost"];
    }
    catch (exception &e) {
        cerr << MQTT << "could not read websiteConfig.json" << endl;
        cerr << MQTT << "error: " << e.what() << endl;
#ifdef DEBUG_MODE
        cout << MQTT << "Server created with default mqtt-port 1883 on 127.0.0.1" << endl;
#endif
        this->port = 1883;
        this->host = "127.0.0.1";
    }
    */

    mosqpp::lib_init();
    this->id = id;
    this->keepalive = 60;
    this->host = host;
    this->port = port;
    this->publish_topic = publish_topic;
    this->subscription_topic_list = subscription_topic_list;

    this->network_connection_access = network_connection_access;
    this->network_connection_read = network_connection_read;
    this->network_connection_write = network_connection_write;
    this->message = message;

};

Mqtt::~Mqtt() {
    disconnect();
    loop_stop();
    mosqpp::lib_cleanup();
}

void Mqtt::connect_mqtt(){
    /*
     * Connect to an MQTT broker. This is a non-blocking call. If you use mosquitto_connect_async your client must use
     * the threaded interface mosquitto_loop_start.
     */
    connect_async(this->host.c_str(), this->port, this->keepalive);
    loop_start();

    for (int i=0; i<200 && !connected; i++) {
#ifdef DEBUG_MODE
        cout << MQTT_CPP << "connecting..." << endl;
#endif
        sleep(1);
    }
    subscribe();
}

bool Mqtt::publish(string message)
{
    /*
     * NULL: pointer to an int.  If not NULL, the function will set this to the message id of this particular message.
     * This can be then used with the publish callback to determine when the message has been sent.
     * Note that although the MQTT protocol doesn’t use message ids for messages with QoS=0, libmosquitto assigns them
     * message ids so they can be tracked with this parameter.
     *
     * publish_topic.c_str(): null terminated string of the topic to publish to.
     *
     * message.length(): the size of the payload (bytes). Valid values are between 0 and 268,435,455.
     *
     * message.c_str(): pointer to the data to send.  If message.length() > 0 this must be a valid memory location.
     *
     * 1: integer value 0, 1 or 2 indicating the Quality of Service to be used for the message.
     *
     * false: set to true to make the message retained.
     *
     */
    int answer = mosqpp::mosquittopp::publish(nullptr, publish_topic.c_str(), static_cast<int>(message.length()), message.c_str(), 1, false);
    return (answer == MOSQ_ERR_SUCCESS);
}

bool Mqtt::subscribe() {
    bool success = true;
    for(int i=0; i<static_cast<int>(subscription_topic_list.size()); i++){
        int answer = mosquittopp::subscribe(nullptr, subscription_topic_list[static_cast<unsigned long>(i)].c_str());
        if(answer != MOSQ_ERR_SUCCESS){
            success = false;
        }
    }
    return success;
}

void Mqtt::on_subscribe(int, int, const int *) {
#ifdef DEBUG_MODE
    cout << MQTT_CPP <<"Subscription succeeded." << endl;
#endif
}

void Mqtt::on_message(const struct mosquitto_message *message) {

    string payload = string(static_cast<char *>(message->payload));
    string topic = string(message->topic);


    sem_wait(network_connection_write);
    sem_wait(network_connection_access);

    *this->message = payload;

    sem_post(network_connection_access);
    sem_post(network_connection_read);

#ifdef DEBUG_MODE
    cout << MQTT_CPP << "data received" << endl;
    cout<< MQTT_CPP << "payload: " << payload << endl;
    cout<< MQTT_CPP << "topic: " << topic << endl;
#endif
}

void Mqtt::on_disconnect(int rc) {
#ifdef DEBUG_MODE
    cout << MQTT_CPP << "disconnection(" << rc << ")" << endl;
#endif
    connected = false;
}

void Mqtt::on_connect(int rc)
{
    if ( rc == 0 ) {
#ifdef DEBUG_MODE
        cout << MQTT_CPP << "connected with server" << endl;
#endif
        connected = true;
    } else {
        cerr << MQTT_CPP << "impossible to connect with server(" << rc << ")" << endl;
    }
}

void Mqtt::on_publish(int mid)
{
#ifdef DEBUG_MODE
    cout << MQTT_CPP << "Message (" << mid << ") succeed to be published " << endl;
#endif
}
