#include<Arduino.h>
#include "task_sensor_acs712.h"
#include "task_sensor_zmpt101b.h"
#include "task_mqtt.h"
#include <esp_task_wdt.h>

void setup(){
  Serial.begin(9600);

  // xTaskCreatePinnedToCore(task_sensor_acs712, "Task Sensor ACS", 4096, NULL, 1, NULL, 1);
  // xTaskCreatePinnedToCore(task_sensor_zmpt101b, "Task Sensor ZMPT", 4096, NULL, 1, NULL, 1);
  Serial.println("Creating task...");
  xTaskCreatePinnedToCore(mqtt_task, "MQTT Task", 4096, NULL, 1, NULL, 1);
  Serial.println("Created task...");

}

void loop(){

}

// #include <WiFi.h>
// #include <PubSubClient.h>

// // WiFi
// const char *ssid = "P201";
// const char *password = "Cuong123456789";

// // MQTT Broker
// const char *mqtt_broker = "broker.hivemq.com";
// const char *topic = "emqx/esp32/daocm";
// // const char *mqtt_username = "emqx";
// // const char *mqtt_password = "public";
// const int mqtt_port = 1883;

// WiFiClient espClient;
// PubSubClient client(espClient);

// void callback(char *topic, byte *payload, unsigned int length) {
//     Serial.print("Message arrived in topic: ");
//     Serial.println(topic);
//     Serial.print("Message:");
//     for (int i = 0; i < length; i++) {
//         Serial.print((char) payload[i]);
//     }
//     Serial.println();
//     Serial.println("-----------------------");
// }

// void setup() {
//     // Set software serial baud to 115200;
//     Serial.begin(9600);
//     // Connecting to a WiFi network
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.println("Connecting to WiFi..");
//     }
//     Serial.println("Connected to the Wi-Fi network");
//     //connecting to a mqtt broker
//     client.setServer(mqtt_broker, mqtt_port);
//     client.setCallback(callback);
//     while (!client.connected()) {
//         String client_id = "esp32-client-";
//         client_id += String(WiFi.macAddress());
//         Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
//         if (client.connect(client_id.c_str())) {
//             Serial.println("Public EMQX MQTT broker connected");
//         } else {
//             Serial.print("failed with state ");
//             Serial.print(client.state());
//             delay(2000);
//         }
//     }
//     // Publish and subscribe
//     client.publish(topic, "Hi, I'm ESP32 ^^");
//     client.subscribe(topic);
// }



// void loop() {
//     client.loop();
// }