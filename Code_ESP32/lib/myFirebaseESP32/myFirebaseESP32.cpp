#include "myFirebaseESP32.h"
#include <Arduino.h>
#include <FirebaseESP32.h>

FirebaseData fbdt;

myFirebaseESP32::myFirebaseESP32()
{
    ;
}

// Cấu hình firebase
void myFirebaseESP32::init()
{
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
}

// Gửi dữ liệu kiểu int
void myFirebaseESP32::putInt(String path, int data)
{
    Firebase.setInt(fbdt, path, data);

    if (fbdt.dataType() == "int")
    {
        Serial.println("Data sent to Firebase successfully!");
    }
    else
    {
        Serial.println("Error sending data to Firebase.");
        Serial.println(fbdt.errorReason());
    }
}

// Gửi dữ liệu kiểu float
void myFirebaseESP32::putFloat(String path, float data)
{
    Firebase.setFloat(fbdt, path, data);

    if (fbdt.dataType() == "float")
    {
        Serial.println("Data sent to Firebase successfully!");
    }
    else
    {
        Serial.println("Error sending data to Firebase.");
        Serial.println(fbdt.errorReason());
    }
}

// Gửi dữ liệu kiểu String
void myFirebaseESP32::putString(String path, String data)
{
    Firebase.setString(fbdt, path, data);

    if (fbdt.dataType() == "string")
    {
        Serial.println("Data sent to Firebase successfully!");
    }
    else
    {
        Serial.println("Error sending data to Firebase.");
        Serial.println(fbdt.errorReason());
    }
}

// Đọc dữ liệu kiểu int
int myFirebaseESP32::readInt(String path)
{
    Firebase.getInt(fbdt, path);
    return fbdt.intData();
}

// Đọc dữ liệu kiểu float
float myFirebaseESP32::readFloat(String path)
{
    Firebase.getFloat(fbdt, path);
    return fbdt.floatData();
}

// Đọc dữ liệu kiểu String
String myFirebaseESP32::readString(String path)
{
    Firebase.getString(fbdt, path);
    return fbdt.stringData();
}