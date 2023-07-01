#include "myNTP.h"
#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

myNTP::myNTP()
{
    ;
}

// Cấu hình RS485
void myNTP::initNTP()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    timeClient.begin();
    timeClient.setTimeOffset(+7 * 60 * 60);
    timeClient.update();
}

String myNTP::getTime()
{
    timeClient.update();

    time_t rawTime = timeClient.getEpochTime();
    struct tm *timeInfo;
    timeInfo = localtime(&rawTime);

    char timeString[20];
    strftime(timeString, sizeof(timeString), "%H:%M %d-%m-%Y", timeInfo);

    return timeString;
}