#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, 1);

const char *ssid = "SECRET_SSID";
const char *password = "SECRET_PASS";

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "172.20.10.2";

unsigned long prevTime = 0;

void setup_wifi(){
  delay(10);
  Serial.print("Łączenie z: ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("Połączono");
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());
  
}

void reconnect(){
  while(!client.connected()){
    Serial.println("Proba poleczenia MQTT");
    String clientId = "StacjaPogody"; // na przyszłość wygenerowac na podstawie mac 
    if(client.connect(clientId.c_str())){
      Serial.println("Poloczono");
    }else{
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883);
  setup_wifi();

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("Blad wysietlacza(nie znaleziono)"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,10);
  display.println("Termometr ESP32");
  display.display();
  delay(2000);
}

void loop() {
  if(!client.connected()){
    reconnect();
  }

  client.loop();

  unsigned long now = millis();
  if( now - prevTime > 5000){
    prevTime = now;

    float humidity = dht.readHumidity();
    float temp = dht.readTemperature();

    if(isnan(humidity) || isnan(temp)){
      Serial.println("Blad pomiaru");
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Status: OK");

    display.setTextSize(1.8,2);
    display.setCursor(0, 20);
    display.print("Temp: ");
    display.print(temp, 1);
    display.println(" C");

    display.setCursor(0, 45);
    display.print("Wilg: ");
    display.print(humidity, 0);
    display.println(" %");

    client.publish("stacja/temperatura", String(temp).c_str());
    client.publish("stacja/wilgotnosc", String(humidity).c_str());

    display.display();
    delay(2000);
  }
}
