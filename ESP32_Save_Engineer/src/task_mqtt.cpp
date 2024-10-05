#include "task_mqtt.h"
#include<Arduino.h>
#include<WiFi.h>
#include<PubSubClient.h>
#include<ArduinoJson.h>
#include <esp_task_wdt.h>


//Cấu hình Wifi
const char *ssid = "P201";
const char *password = "Cuong123456789";


//Cấu hình MQTT Broker
const char *mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;
// const char *topic = "holken233A/bastu/humid";
const char *topic_acs712 = "sensor/acs712_zmpt101b";
// const char *topic_zmpt = "emqx/esp32/daocm";

WiFiClient espClient;
PubSubClient client(espClient);

QueueHandle_t currentQueue;
QueueHandle_t voltageQueue;

void setup_wifi(){
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, unsigned char *payload, unsigned int lenght){
    std::unique_ptr<char[]> message (new char[lenght+1]);
    memcpy(message.get(), payload, lenght);
    message[lenght] = '\0';

    Serial.print("Message reviced: ");
    Serial.println(message.get());

    //Phan tich chuoi thanh JSON
    std::unique_ptr<DynamicJsonDocument> doc (new DynamicJsonDocument (4096));
    DeserializationError error_parse = deserializeJson(*doc, message.get());

    if(error_parse){
        Serial.print("Failed to parse JSON: ");
        Serial.println(error_parse.c_str());
        return;
    }
    if(doc->containsKey("device_info")){
        JsonObject deviceInfo = (*doc)["device_info"];
        String deviceInfoStr;
        serializeJson(deviceInfo, deviceInfoStr);
        Serial.print("Device info JSON");
        Serial.println(deviceInfoStr);
    }

    if(doc->containsKey("sensor_data")){
        float acs712Value = (*doc)["sensor_data"]["acs712"]["current"]["value"];
        std::unique_ptr<DynamicJsonDocument> messagePublish(new DynamicJsonDocument(256));

        if(acs712Value > 2){
            (*messagePublish)["value"] = acs712Value;
            (*messagePublish)["state"] = "on";
        }
    
        String messagePublishStr;

        serializeJson(*messagePublish, messagePublishStr);
        client.publish(topic_acs712, messagePublishStr.c_str());
        Serial.print("Publish successfully to topic: ");
        Serial.println(topic_acs712);
    }

}

void setup_mqtt(){
    client.setServer(mqtt_broker, mqtt_port);
    client.setBufferSize(2048);
    Serial.println("Set callback...");
    client.setCallback(callback);

    while(!client.connected()){
        Serial.print("Connecting to MQTT...");
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        if(client.connect(client_id.c_str())){
            Serial.println("Connected to MQTT Broker!!!");
            Serial.println("--------------------------------");
        }
        else{
            Serial.print("Connected failed, rc = ");
            Serial.println(client.state());
            vTaskDelay(2000/portTICK_PERIOD_MS);

        }

    }
    // client.publish(topic, "Hi, I'm ESP32 ^^");
    client.subscribe(topic_acs712);
    // client.subscribe(topic_zmpt);
    client.subscribe(topic_acs712);

}

void mqtt_task(void *pvParameters){
    // Thiết lập kết nối WiFi ban đầu
    setup_wifi();
    setup_mqtt();

    esp_task_wdt_delete(NULL);

    while(true){
        client.loop();

        vTaskDelay(100/portTICK_PERIOD_MS);
    }



}


