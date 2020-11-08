#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "EspMQTTClient.h"
#include <ArduinoJson.h>
#include <NeoPixelBus.h>
#include <ColorConverterLib.h>

Adafruit_PWMServoDriver robot = Adafruit_PWMServoDriver(0x41);
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)


#define MQTT_SERVER_IP    "192.168.1.102"
#define MQTT_USERNAME     "andrik_1"
#define MQTT_PASSWORD     "magpiecrow"
#define MQTT_CLIENT_NAME  "HackEd_Robot"    //this should be a "random" value. This value is ignored if you call WiFiMQTTclient.enableMACaddress_for_ClientName();
#define MQTT_SERVER_PORT  1883

#define WIFI_SSID         "TELUS0357"
#define WIFI_PASS         "77kmm7r7hz"

const uint16_t PixelCount = 29;
const uint8_t PixelPin = 12;
#define colorSaturation 128
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);
HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);
double hue;
double saturation;
double lighting;

const char* MQTT_Confirmation_Topic = "hacked/robot/confirmation";
const char* MQTT_Debug_Topic = "hacked/robot/debug";
bool initialConnectionEstablished_Flag = false;   //used to detect first run after power up

String input;

int current_servo_pos = 90;

//bool initialConnectionEstablished_Flag = false;   //used to detect first run after power up

EspMQTTClient WiFiMQTTclient(
  WIFI_SSID,
  WIFI_PASS,
  MQTT_SERVER_IP,   // MQTT Broker server ip
  MQTT_USERNAME,    // Can be omitted if not needed
  MQTT_PASSWORD,    // Can be omitted if not needed
  MQTT_CLIENT_NAME, // Client name that uniquely identify your device
  MQTT_SERVER_PORT  // The MQTT port, default to 1883. this line can be omitted
);

void loop() {
  
  WiFiMQTTclient.loop();
/*
  if (WiFiMQTTclient.isWifiConnected()) {     //check for WiFi connect
    Serial.println("WiFi Disconnected");
    for(int i = 0; i < PixelCount; i+=4) {
      strip.SetPixelColor(i-1, black);
      strip.SetPixelColor(i, green);
      strip.SetPixelColor(i+1, black);
      strip.SetPixelColor(i+2, green);
      strip.Show();
    }
  }
  */
  if (!WiFiMQTTclient.isWifiConnected()) {     //check for WiFi disconnect
    Serial.println("WiFi Disconnected");
    for(int i = 0; i < PixelCount; i+=4) {
      strip.SetPixelColor(i-1, black);
      strip.SetPixelColor(i, red);
      strip.SetPixelColor(i+1, black);
      strip.SetPixelColor(i+2, blue);
      strip.Show();
    }
  }
  else if (!WiFiMQTTclient.isMqttConnected()) {  //wait for MQTT connect
    Serial.println("MQTT Disconnected");
    for(int i = 0; i < PixelCount; i+=4) {
      strip.SetPixelColor(i-1, black);
      strip.SetPixelColor(i, red);
      strip.SetPixelColor(i+1, black);
      strip.SetPixelColor(i+2, black);
      strip.Show();
    }
  }
  
/*
  forward();
  delay(1000);
  reverse();
  delay(1000);
  left();
  delay(1000);
  right();
  delay(1000);
  freeze();
  delay(1000);

  if(Serial.available() > 0)  {
    input = Serial.readString();
    Serial.println(input);
  }
  robot.setPWM(0, 0, input.toInt());
  robot.setPWM(1, 0, input.toInt());
  */
}
