#ifndef myNTP_h
#define myNTP_h

#include <Arduino.h>

class myNTP
{
public:
    myNTP();

    void initNTP();
    String getTime();

private:
#define WIFI_SSID "BookTS"
#define WIFI_PASSWORD "12345678"
};
#endif