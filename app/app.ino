#include "HardwareMappings.h"
#include "SlotSensor.h"

SlotSensor sensors[NUMBER_OF_SENSORS];

unsigned long previouConfirm = 0;
unsigned long previousSerialSend = 0;

long interval = 2000;

void initSensors()
{
    int i = 0;
    for (int spin : sensorPin)
    {
        pinMode(spin, INPUT);
        sensors[i] = SlotSensor(i, spin);
        i++;
    }
}

void readSensors()
{
    for (int i = 0; i < NUMBER_OF_SENSORS; i++)
    {
        sensors[i].readSensor();
    }
}

void confirmSensors()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previouConfirm > interval)
    {
        previouConfirm = currentMillis;

        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
        {
            if (sensors[i].hasChanged())
            {
                sensors[i].readSensor();
                if (sensors[i].hasChanged())
                {
                    sensors[i].confirmChange();
                }
            }
        }
    }
}

void serialSendSensor(int i)
{
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println((sensors[i].occupied) ? "occupied" : "empty");
}

void serialSendSensors()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousSerialSend > interval)
    {
        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
        {
            serialSendSensor(i);
        }
    }
}

void setup()
{
    Serial.begin(9600);
    initSensors();
    pinMode(26, OUTPUT);
    digitalWrite(26, LOW);
}

void loop()
{
    readSensors();
    confirmSensors();
    serialSendSensors();
}
