
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <stdint.h>


class Motor
{
private:
    uint8_t pin1;
    uint8_t pin2;

public:
    Motor(uint8_t pin1, uint8_t pin2)
    {
        // Remember pin numbers
        this->pin1 = pin1;
        this->pin2 = pin2;

        // Configure GPIO as outputs
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
    }
    
    void stop()
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
    }

    void reverse()
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    }

    void forward()
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
    }
};

#endif
