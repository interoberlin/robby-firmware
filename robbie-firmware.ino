

/*
 * Pinout for L298 motor driver
 */
#define PIN_L298_IN1  8
#define PIN_L298_IN2  9
#define PIN_L298_IN3 10
#define PIN_L298_IN4 11

/*
 * Serial control chars
 */
#define CHAR_STOP       'S'
#define CHAR_FORWARD    'F'
#define CHAR_BACKWARD   'B'
#define CHAR_FORWARD_LEFT   'l'
#define CHAR_FORWARD_RIGHT  'r'
#define CHAR_BACKWARD_LEFT  'L'
#define CHAR_BACKWARD_RIGHT 'R'

/*
 * State machine
 */
typedef enum
{
  STATE_STOP,
  STATE_FORWARD,
  STATE_BACKWARD
} state_t;
state_t state = STATE_STOP;


#include "motor.hpp"

Motor motorLeft(PIN_L298_IN1, PIN_L298_IN2);
Motor motorRight(PIN_L298_IN3, PIN_L298_IN4);
MotorPair motors(&motorLeft,&motorRight);

void setup()
{
  Serial.begin(9600);
  motors.stop();
}

void loop()
{
  delay(10);

  if (Serial.available() > 0)
  {
    uint8_t c = Serial.read();
    
    switch (c)
    {
      case CHAR_STOP:
        state = STATE_STOP;
        break;
      case CHAR_FORWARD:
        state = STATE_FORWARD;
        break;
      case CHAR_BACKWARD:
        state = STATE_BACKWARD;
        break;
      case '1':
        motors.setSpeed(128);
        break;
      case '2':
        motors.setSpeed(255);
        break;
    }
  }

  switch (state)
  {
    case STATE_FORWARD:
      motors.forward();
      break;
    case STATE_BACKWARD:
      motors.backward();
      break;
    default:
      motors.stop();
      break;
  }
}

