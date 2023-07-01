#ifndef myVX4_h
#define myVX4_h

#include <Arduino.h>

class myVX4
{
public:
    myVX4();

    void configVX4(int baudrate, int timeout);
    uint16_t calculateCRC(uint8_t *data, uint8_t length);
    float readSetPoint();
    float readTempAlarm();
    float readTempDelta1();
    float readTempDelta2();

    void controlSetPoint(int temp);
    void tempDelta2(int temp);
    void tempAlarm(int temp);
    void tempDelta1(int temp);

private:
};
#endif