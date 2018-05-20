

/*
 * Pinout for L298 motor driver
 */
#define PIN_L298_IN1  8
#define PIN_L298_IN2  9
#define PIN_L298_IN3 10
#define PIN_L298_IN4 11


#include "motor.hpp"

Motor motorLeft(PIN_L298_IN1, PIN_L298_IN2);
Motor motorRight(PIN_L298_IN3, PIN_L298_IN4);


void setup()
{
  Serial.begin(9600);
  motorLeft.stop();
  motorRight.stop();
}

void loop()
{
  Serial.write("Hello world!\n");
  delay(1000);
  motorLeft.forward();
  delay(1000);
  motorLeft.stop();
  delay(1000);
  motorRight.forward();
  delay(1000);
  motorRight.stop();
}

