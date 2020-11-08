
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  robot.setPWM(n, 0, pulse);
}

void right()  {
  robot.setPWM(0, 0, 370);
  robot.setPWM(1, 0, 373);
}

void left()  {
  robot.setPWM(0, 0, 364);
  robot.setPWM(1, 0, 367);
}


void forward() {
  robot.setPWM(0, 0, 392);
  robot.setPWM(1, 0, 345);
}

void reverse()  {
  robot.setPWM(0, 0, 342);
  robot.setPWM(1, 0, 395);
}

void freeze() {
  robot.setPWM(0, 0, 368);
  robot.setPWM(1, 0, 370);
}
