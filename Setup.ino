
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  strip.Begin();
  strip.Show();

  robot.begin();
  
  robot.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  WiFiMQTTclient.enableHTTPWebUpdater();    // Enable the web firmware updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overwritten with enableHTTPWebUpdater("user", "password").
  //  WiFiMQTTclient.enableLastWillMessage("IoT/lastwill", "Goodbye");  // You can activate the retain flag by setting the third parameter to true
  WiFiMQTTclient.enableMQTTConnect();       //use this to enable MQTT connections.  If you comment this line out than you can use this with a WiFi only connection.
  //WiFiMQTTclient.enableMACaddress_for_ClientName(); //This will use the WiFi hardware MAC address for the client name instead of the value
  int pos = map(135, 0, 270, 120, 520);
  String servo_Pos = String(pos);
  robot.setPWM(2, 0, pos);
  current_servo_pos = 90;
  WiFiMQTTclient.publish(MQTT_Debug_Topic, servo_Pos);
}


void onConnectionEstablished() {
  if (!initialConnectionEstablished_Flag) {     //execute this the first time we have established a WiFi and MQTT connection after powerup
    initialConnectionEstablished_Flag = true;

    //  display IP address.
    Serial.println("\nIP address: ");
    Serial.println(WiFi.localIP());

    // Subscribe to mqtt channels
    WiFiMQTTclient.subscribe("hacked/robot/movement", movement_Handler);
    WiFiMQTTclient.subscribe("hacked/robot/pan", pan_Handler);
    WiFiMQTTclient.subscribe("hacked/robot/rgb", rgb2_Handler);


    // print MQTT info via serial
    Serial.println("");
    Serial.println(WiFiMQTTclient.getMqttClientName());
    Serial.println(WiFiMQTTclient.getMqttServerIp());
    Serial.println(WiFiMQTTclient.getMqttServerPort());
    Serial.println(WiFiMQTTclient.getConnectionEstablishedCount());
    //WiFiMQTTclient.publish(MQTT_Debug_Topic, "IP: ");
    //String IP = WiFi.localIP();
    //WiFiMQTTclient.publish(MQTT_Debug_Topic, IP);
    for(int i = 0; i < PixelCount; i+=3) {
      strip.SetPixelColor(i, black);
      strip.SetPixelColor(i+1, white);
      strip.SetPixelColor(i+2, white);
      strip.SetPixelColor(i+3, black);
      strip.Show();
    }
  }
  else {
    for(int i = 0; i < PixelCount; i+=3) {
      strip.SetPixelColor(i, black);
      strip.SetPixelColor(i+1, white);
      strip.SetPixelColor(i+2, white);
      strip.SetPixelColor(i+3, black);
      strip.Show();
    }
  }
}
