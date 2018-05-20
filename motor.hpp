
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <stdint.h>


class Motor
{
private:
    uint8_t pin1;
    uint8_t pin2;
    uint8_t speed;

public:
    Motor(uint8_t pin1, uint8_t pin2)
    {
        // Remember pin numbers
        this->pin1 = pin1;
        this->pin2 = pin2;
        this->speed = 255;

        // Configure GPIO as outputs
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
    }
    
    void stop()
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, 0);
    }

    void forward()
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, speed);
    }

    void backward()
    {
        analogWrite(pin1, speed);
        analogWrite(pin2, 0);
    }

    void setSpeed(uint8_t value)
    {
        speed = value;
    }
};

#endif
