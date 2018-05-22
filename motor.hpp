
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <stdint.h>


typedef enum
{
    DIRECTION_STOP,
    DIRECTION_FORWARD,
    DIRECTION_BACKWARD
} motor_direction_t;


/**
 * Bundles abstract methods to control one motor via an L298
 */
class Motor
{
private:
    uint8_t pin1;
    uint8_t pin2;
    uint8_t speed;
    motor_direction_t direction;

public:
    Motor(uint8_t pin1, uint8_t pin2)
    {
        // Remember pin numbers
        this->pin1 = pin1;
        this->pin2 = pin2;

        // Configure GPIO as outputs
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);

        speed = 255;
        stop();
    }
    
    void stop()
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, 0);
        direction = DIRECTION_STOP;
    }

    void forward()
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, speed);
        direction = DIRECTION_FORWARD;
    }

    void backward()
    {
        analogWrite(pin1, speed);
        analogWrite(pin2, 0);
        direction = DIRECTION_BACKWARD;
    }

    void setSpeed(uint8_t value)
    {
        speed = value;

        // Repeat last command
        switch (direction)
        {
            case DIRECTION_FORWARD:
                forward();
                break;
            case DIRECTION_BACKWARD:
                backward();
                break;
        }
    }
};


/**
 * Two motors drive one axis
 */
class MotorPair
{
private:
    Motor* motorLeft;
    Motor* motorRight;
    uint8_t speed;

public:
    MotorPair(Motor* motorLeft, Motor* motorRight)
    {
        this->motorLeft = motorLeft;
        this->motorRight = motorRight;

        // We don't know the motors' speed, therefore stop them.
        motorLeft->stop();
        motorRight->stop();
        speed = 96;
        setSpeed(speed);
    }

    void setSpeed(uint8_t value)
    {
        speed = value;
        motorLeft->setSpeed(value);
        motorRight->setSpeed(value);
    }

    void stop()
    {
        motorLeft->stop();
        motorRight->stop();
    }

    void forward()
    {
        motorLeft->setSpeed(speed);
        motorRight->setSpeed(speed);
        motorLeft->forward();
        motorRight->forward();
    }

    void backward()
    {
        motorLeft->setSpeed(speed);
        motorRight->setSpeed(speed);
        motorLeft->backward();
        motorRight->backward();
    }

    void moveLeft()
    {
        motorLeft->setSpeed(speed);
        motorRight->setSpeed(speed+20);
        motorLeft->forward();
        motorRight->forward();
    }

    void moveRight()
    {
        motorLeft->setSpeed(speed+20);
        motorRight->setSpeed(speed);
        motorLeft->forward();
        motorRight->forward();
    }

    void rotateLeft()
    {
        motorLeft->setSpeed(speed);
        motorRight->setSpeed(speed);
        motorLeft->backward();
        motorRight->forward();
    }

    void rotateRight()
    {
        motorLeft->setSpeed(speed);
        motorRight->setSpeed(speed);
        motorLeft->forward();
        motorRight->backward();
    }
};

#endif
