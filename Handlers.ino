void movement_Handler (const String & payload) {
  if(payload.equals("forward"))  {
    Serial.println("moving forward");
    WiFiMQTTclient.publish(MQTT_Confirmation_Topic, "moving forward");
    forward();
  }
  if(payload.equals("reverse"))  {
    Serial.println("moving backwards");
    WiFiMQTTclient.publish(MQTT_Confirmation_Topic, "moving backwards");
    reverse();
  }
  if(payload.equals("left"))  {
    Serial.println("turning left");
    WiFiMQTTclient.publish(MQTT_Confirmation_Topic, "turning left");
    left();
  }
  if(payload.equals("right"))  {
    Serial.println("turning right");
    WiFiMQTTclient.publish(MQTT_Confirmation_Topic, "turning right");
    right();
  }
  if(payload.equals("freeze"))  {
    Serial.println("freezing");
    WiFiMQTTclient.publish(MQTT_Confirmation_Topic, "freezing");
    freeze();
  }
}


void pan_Handler (const String & payload) {
  int pos = map(payload.toInt(), 0, 270, 120, 520);
  String servo_Pos = String(pos);
  current_servo_pos = pos;
  robot.setPWM(2, 0, pos);
  WiFiMQTTclient.publish(MQTT_Debug_Topic, servo_Pos);
  //WiFiMQTTclient.publish(MQTT_Debug_Topic, current_servo_pos);

}


void rgb2_Handler (const String & payload) {
  Serial.print("RGB2_handler running");
  Serial.println(payload);

 StaticJsonDocument<100> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, payload);

  int b = doc["b"]; 
  int r = doc["r"];
  int g = doc["g"];

 ColorConverter::RgbToHsl(r, g, b, hue, saturation, lighting);

 for(int i = 0; i <= PixelCount; i++) {
      strip.SetPixelColor(i, HslColor(hue, saturation, lighting));
      strip.Show();
    }
}
