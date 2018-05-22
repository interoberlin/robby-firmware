

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
//#define CHAR_FORWARD_LEFT   'l'
//#define CHAR_FORWARD_RIGHT  'r'
#define CHAR_LEFT       'L'
#define CHAR_RIGHT      'R'
#define CHAR_ROTATE_LEFT  '<'
#define CHAR_ROTATE_RIGHT '>'

/*
 * State machine
 */
typedef enum
{
  STATE_STOP,
  STATE_FORWARD,
  STATE_BACKWARD,
  STATE_LEFT,
  STATE_RIGHT,
  STATE_ROTATE_LEFT,
  STATE_ROTATE_RIGHT,
} state_t;
state_t state = STATE_STOP;


#include "motor.hpp"

Motor motorLeft(PIN_L298_IN1, PIN_L298_IN2);
Motor motorRight(PIN_L298_IN3, PIN_L298_IN4);
MotorPair motors(&motorLeft,&motorRight);

uint32_t command_timeout = 0;


void setup()
{
  Serial.begin(9600);
  motors.stop();
}


void loop()
{
  delay(10);
  if (state != STATE_STOP)
  {
    command_timeout++;
  }

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
      case CHAR_LEFT:
        state = STATE_LEFT;
        break;
      case CHAR_RIGHT:
        state = STATE_RIGHT;
        break;
      case CHAR_ROTATE_LEFT:
        state = STATE_ROTATE_LEFT;
        break;
      case CHAR_ROTATE_RIGHT:
        state = STATE_ROTATE_RIGHT;
        break;
      case '1':
        motors.setSpeed(128);
        break;
      case '2':
        motors.setSpeed(160);
        break;
      case '3':
        motors.setSpeed(192);
        break;
      case '4':
        motors.setSpeed(224);
        break;
      case '5':
        motors.setSpeed(255);
        break;
    }

    command_timeout = 0;
  }

  if (command_timeout > 200)
  {
    state = STATE_STOP;
  }

  switch (state)
  {
    case STATE_FORWARD:
      motors.forward();
      break;
    case STATE_BACKWARD:
      motors.backward();
      break;
    case STATE_LEFT:
      motors.moveLeft();
      break;
    case STATE_RIGHT:
      motors.moveRight();
      break;
    case STATE_ROTATE_LEFT:
      motors.rotateLeft();
      break;
    case STATE_ROTATE_RIGHT:
      motors.rotateRight();
      break;
    default:
      motors.stop();
      break;
  }
}

