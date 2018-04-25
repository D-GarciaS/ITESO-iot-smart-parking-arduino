#ifndef Morse_h
#define Morse_h

#include "SlotSensor.h"
#include "Arduino.h"

SlotSensor::SlotSensor(int number, int pin)
{
    this->number = number;
    this->pin = pin;
    preferential = true;
    occupied = false;
    changed = false;
    lastRead = 0;
}

bool SlotSensor::hasChanged() { return changed; }

void SlotSensor::confirmChange()
{
    if (changed)
    {
        occupied = !occupied;
    }
}

void SlotSensor::readSensor()
{
    bool res = digitalRead(pin);
    if (res != occupied)
    {
        changed = true;
    }
    else
    {
        changed = false;
    }
}

#endif
