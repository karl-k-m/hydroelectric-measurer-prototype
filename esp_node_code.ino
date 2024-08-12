include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHTesp.h> // Include the DHTesp library
#include <PubSubClient.h>
#include <base64.h> // Include the Base64 library

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

const char* ssid = "SSID";
const char* password = "PASSWORD";

const char* serverName = "http://server.com/api/";

const char* device_id = "1";

// MQTT settings
const char* mqtt_server = "192.168.11.11";
const int mqtt_port = 1883;
const char* mqtt_user = "mqtt_user";
const char* mqtt_password = "mqtt_password";

WiFiClient espClient;
PubSubClient client(espClient);

// Water detection sensor pins (our prototype used 5 sensors)
#define SENSOR_PIN_1 D1
#define SENSOR_PIN_2 D2
#define SENSOR_PIN_3 D3
#define SENSOR_PIN_4 D4

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Setup DHT sensor
  dht.setup(D7, DHTesp::DHT11); 
  
  // Setup water detection sensors
  pinMode(SENSOR_PIN_1, INPUT_PULLUP);
  pinMode(SENSOR_PIN_2, INPUT_PULLUP);
  pinMode(SENSOR_PIN_3, INPUT_PULLUP);
  pinMode(SENSOR_PIN_4, INPUT_PULLUP);

  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  connectToMQTT();
}

void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void sendMQTTData(float temperature, float humidity, int highestWaterLevel) {
  String payload = String(temperature, 1) + "," + String(humidity, 1) + "," + String(highestWaterLevel);
  client.publish("sensor/data", payload.c_str());
}

void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  delay(dht.getMinimumSamplingPeriod());

  // Read temperature and humidity from DHT sensor
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read water detection sensor values
  int sensorValues[4];
  sensorValues[0] = digitalRead(SENSOR_PIN_1);
  sensorValues[1] = digitalRead(SENSOR_PIN_2);
  sensorValues[2] = digitalRead(SENSOR_PIN_3);
  sensorValues[3] = digitalRead(SENSOR_PIN_4);

  // Find the highest water level sensor that is triggered
  int highestWaterLevel = 0;
  for (int i = 0; i < 4; i++) {
    if (sensorValues[i] == LOW) {
      highestWaterLevel = i + 1;
    }
  }

  sendMQTTData(temperature, humidity, highestWaterLevel);
  // Get the current time
  String timestamp = "2024-05-26T14:00:00Z"; // Should be handled at server level for accurate timestamp

  // Prepare JSON payload
  String jsonPayload = "{\"device_id\":\"" + String(device_id) + "\",\"sensors\":[";
  jsonPayload += "{\"sensor_id\":\"1\",\"value\":" + String(temperature, 1) + ",\"timestamp\":\"" + timestamp + "\"},";
  jsonPayload += "{\"sensor_id\":\"2\",\"value\":" + String(humidity, 1) + ",\"timestamp\":\"" + timestamp + "\"},";
  jsonPayload += "{\"sensor_id\":\"3\",\"value\":" + String(highestWaterLevel) + ",\"timestamp\":\"" + timestamp + "\"}";
  jsonPayload += "]}";

  // Send payload
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(espClient, serverName); // Use espClient and serverName
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  // Wait for 10 seconds before next read (testing delay. production system would have a delay of 30-60 minutes.)
  delay(10000);
}
